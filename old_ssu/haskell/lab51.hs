average :: [Double] -> Double                                                                       --1
average s = (foldr (+) 0 s)/fromIntegral(length s)

scalmult :: Num a => [a] -> [a] -> [a]                                                              --2
scalmult = zipWith (*)

countEven :: Integral a => Num a => Eq a => [a] -> Int                                              --3
countEven b = length(filter(\x -> rem x 2 == 0) b)

quicksort1 :: Ord a => [a] -> [a]                                                                   --4
quicksort1 [] = []
quicksort1 (x:xs) = filter(\y -> y<x) (quicksort1 xs) ++ [x] ++ filter(\y -> y>=x) (quicksort1 xs)

quicksort2 :: Ord a => (a -> a -> Bool) -> [a] -> [a]                                               --5
quicksort2 f [] = []
quicksort2 f (x:xs) = filter(f x) (quicksort2 f xs) ++ [x] ++ filter(\y -> not $ f x y) (quicksort2 f xs)