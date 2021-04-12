package main

import (
	"bytes"
	"errors"
	"fmt"
	"image"
	"image/color"
	"image/draw"
	"image/png"
	"math"
	"os"
	"runtime"
	"strconv"
	"sync"
)

var (
	black     color.Color = color.RGBA{0, 0, 0, 255}
	white     color.Color = color.RGBA{255, 255, 255, 255}
	red       color.Color = color.RGBA{255, 0, 0, 255}
	green     color.Color = color.RGBA{0, 255, 0, 255}
	darkgreen color.Color = color.RGBA{64, 128, 0, 255}
	blue      color.Color = color.RGBA{0, 0, 255, 255}
	darkblue  color.Color = color.RGBA{0, 0, 128, 255}
	yellow    color.Color = color.RGBA{255, 255, 0, 255}
	orange    color.Color = color.RGBA{255, 128, 0, 255}
	eps                   = (math.Nextafter(1, 2) - 1) * 10
	h                     = 0.0001
)

func isEqual(a, b float64) bool {
	return math.Abs(a-b) < eps
}

type point struct {
	x float64
	y float64
}

type system struct {
	column [2]float64
}

func (sys system) fill(p point) system {
	sys.column[0] = first(point{p.x, p.y})
	sys.column[1] = second(point{p.x, p.y})

	return sys
}

//Jacobian struct implements matrix of partial derivatives
type Jacobian struct {
	matrix [2][2]float64
}

func (jac Jacobian) fill(p point) Jacobian {
	jac.matrix[0][0] = firstDerbyX(point{p.x, p.y})
	jac.matrix[0][1] = firstDerbyY(point{p.x, p.y})
	jac.matrix[1][0] = secondDerbyX(point{p.x, p.y})
	jac.matrix[1][1] = secondDerbyY(point{p.x, p.y})

	return jac
}

func (jac Jacobian) inverse() (inverseJac Jacobian, err error) {
	detJac := (jac.matrix[0][0] * jac.matrix[1][1]) - (jac.matrix[0][1] * jac.matrix[1][0])
	if isEqual(detJac, 0) {
		return inverseJac, errors.New("Zero determinant of Jacobian")
	}

	inverseJac.matrix[0][0] = jac.matrix[1][1] / detJac
	inverseJac.matrix[0][1] = -jac.matrix[0][1] / detJac
	inverseJac.matrix[1][0] = -jac.matrix[1][0] / detJac
	inverseJac.matrix[1][1] = jac.matrix[0][0] / detJac

	return inverseJac, nil
}

//Functions
func first(p point) float64 {
	return math.Sin(p.x-p.y) - p.x*p.y + 1
}

func second(p point) float64 {
	return p.x*p.x - p.y*p.y - 0.75
}

//Their partial derivatives
func firstDerbyX(p point) float64 {
	return math.Cos(p.x-1) - 1
}

func firstDerbyY(p point) float64 {
	return -math.Cos(p.y-1) - 1
}

func secondDerbyX(p point) float64 {
	return 2 * p.x
}

func secondDerbyY(p point) float64 {
	return 2 * p.y
}

func newton(x0 point, answer [2]point, h float64) (x1 point, color color.Color, err error) {
	const n = 10000
	var (
		jac Jacobian
		sys system
		i   = 0
	)
	sys = sys.fill(x0)
	jac = jac.fill(x0)
	x1 = x0

	for i < n {
		var (
			multofInvJacandSys [2]float64
		)

		sys = sys.fill(x1)
		jac = jac.fill(x1)

		inverseJac, err := jac.inverse()
		if err != nil {
			break
		}

		for i := 0; i < 2; i++ {
			for j := 0; j < 2; j++ {
				multofInvJacandSys[i] += inverseJac.matrix[i][j] * sys.column[j]
			}
		}
		x0 = x1

		x1.x = x0.x - multofInvJacandSys[0]
		x1.y = x0.y - multofInvJacandSys[1]

		if isEqual(first(x1), 0) && isEqual(second(x1), 0) {
			fmt.Println("break")
			break
		}
		i++
	}

	if math.Abs(x1.x-answer[0].x) < h && math.Abs(x1.y-answer[0].y) < h {
		return x1, green, nil
	} else if math.Abs(x1.x-answer[1].x) < h && math.Abs(x1.y-answer[1].y) < h {
		return x1, blue, nil
	} else {
		return x1, red, nil
	}
}

func main() {
	var (
		wg            sync.WaitGroup
		maxProcs      = runtime.NumCPU()
		maxGoroutines = 1048574
		guard         = make(chan struct{}, maxGoroutines)

		answers = [2]point{
			point{1.3210490855091497, 0.9975824208177294},
			point{-1.0125, -0.5246},
		}

		canvasSize = 4000
		scale      int
		gridSize   float64 = 3.9
		gridCenter point
	)

	runtime.GOMAXPROCS(maxProcs)

	//Found scale
	for i := canvasSize; i >= 10; {
		i = i / 10
		scale = canvasSize / i
	}

	gridCenter = point{0, 0}

	graph, err := os.Create("graph.png")
	if err != nil {
		fmt.Println(err)
	}
	defer graph.Close()

	img := image.NewRGBA(image.Rect(0, 0, canvasSize, canvasSize))
	draw.Draw(img, img.Bounds(), &image.Uniform{white}, image.ZP, draw.Src)

	//Grid
	drawGrid(canvasSize, scale, gridSize, gridCenter, img, black)

	gridSize *= float64(scale)
	gridSizei := int(gridSize)

	//Finding points in grid
	for y := canvasSize/2 - gridSizei/2 - int(gridCenter.y*float64(scale/2)) + 1; y < canvasSize/2+gridSizei/2-int(gridCenter.y*float64(scale/2)); y++ {
		for x := canvasSize/2 - gridSizei/2 + int(gridCenter.x*float64(scale/2)) + 1; x < canvasSize/2+gridSizei/2+int(gridCenter.x*float64(scale/2)); x++ {
			guard <- struct{}{}
			wg.Add(1)
			go func(canvasSize, scale, px, py int) {
				fmt.Println(getGID())
				approximation := px2point(canvasSize, scale, px, py)

				_, color, err := newton(approximation, answers, h)
				if err != nil {
					fmt.Println(err)
				}
				img.Set(px, py, color)

				wg.Done()
				<-guard
			}(canvasSize, scale, x, y)

		}
	}
	wg.Wait()

	//Coordinate system
	for x := 0; x < canvasSize; x++ {
		y := canvasSize / 2
		img.Set(x, y, black)
	}
	for y := 0; y < canvasSize; y++ {
		x := canvasSize / 2
		img.Set(x, y, black)
	}

	//Answers
	for _, p := range answers {
		p.Draw(canvasSize, scale, img, orange)
	}

	png.Encode(graph, img)
}

func getGID() uint64 {
	b := make([]byte, 64)
	b = b[:runtime.Stack(b, false)]
	b = bytes.TrimPrefix(b, []byte("goroutine "))
	b = b[:bytes.IndexByte(b, ' ')]
	n, _ := strconv.ParseUint(string(b), 10, 64)
	return n
}

func point2px(canvasSize, scale int, p point) (px, py int) {
	if p.x >= 0 && p.y >= 0 {
		px = canvasSize/2 + int(p.x*float64(scale/2))
		py = canvasSize/2 - int(p.y*float64(scale/2))
	} else if p.x < 0 && p.y >= 0 {
		px = canvasSize/2 - int(p.x*float64(scale/2))
		py = canvasSize/2 - int(p.y*float64(scale/2))
	} else if p.x >= 0 && p.y < 0 {
		px = canvasSize/2 + int(p.x*float64(scale/2))
		py = canvasSize/2 + int(p.y*float64(scale/2))
	} else if p.x < 0 && p.y < 0 {
		px = canvasSize/2 - int(p.x*float64(scale/2))
		py = canvasSize/2 + int(p.y*float64(scale/2))
	}

	return px, py
}

func px2point(canvasSize, scale, px, py int) (p point) {
	if px >= canvasSize/2 && py <= canvasSize/2 {
		p.x = float64(px-canvasSize/2) / float64(scale/2)
		p.y = -float64(py-canvasSize/2) / float64(scale/2)
	} else if px < canvasSize/2 && py <= canvasSize/2 {
		p.x = float64(px-canvasSize/2) / float64(scale/2)
		p.y = -float64(py-canvasSize/2) / float64(scale/2)
	} else if px >= canvasSize/2 && py > canvasSize/2 {
		p.x = float64(px-canvasSize/2) / float64(scale/2)
		p.y = -float64(py-canvasSize/2) / float64(scale/2)
	} else if px < canvasSize/2 && py > canvasSize/2 {
		p.x = float64(px-canvasSize/2) / float64(scale/2)
		p.y = -float64(py-canvasSize/2) / float64(scale/2)
	}

	return p
}

func (p point) Draw(canvasSize, scale int, img *image.RGBA, color color.Color) {
	px, py := point2px(canvasSize, scale, p)
	img.Set(px, py, color)
}

func drawGrid(canvasSize, scale int, gridSize float64, gridCenter point, img *image.RGBA, color color.Color) {
	gridSize *= float64(scale)
	gridSizei := int(gridSize)
	for x := canvasSize/2 - gridSizei/2 + int(gridCenter.x*float64(scale/2)); x < canvasSize/2+gridSizei/2+int(gridCenter.x*float64(scale/2)); x++ {
		y := canvasSize/2 - gridSizei/2 - int(gridCenter.y*float64(scale/2))
		img.Set(x, y, color)
	}
	for x := canvasSize/2 + gridSizei/2 + int(gridCenter.x*float64(scale/2)); x >= canvasSize/2-gridSizei/2+int(gridCenter.x*float64(scale/2)); x-- {
		y := canvasSize/2 + gridSizei/2 - int(gridCenter.y*float64(scale/2))
		img.Set(x, y, color)
	}
	for y := canvasSize/2 - gridSizei/2 - int(gridCenter.y*float64(scale/2)); y < canvasSize/2+gridSizei/2-int(gridCenter.y*float64(scale/2)); y++ {
		x := canvasSize/2 - gridSizei/2 + int(gridCenter.x*float64(scale/2))
		img.Set(x, y, color)
	}
	for y := canvasSize/2 + gridSizei/2 - int(gridCenter.y*float64(scale/2)); y >= canvasSize/2-gridSizei/2-int(gridCenter.y*float64(scale/2)); y-- {
		x := canvasSize/2 + gridSizei/2 + int(gridCenter.x*float64(scale/2))
		img.Set(x, y, color)
	}
}
