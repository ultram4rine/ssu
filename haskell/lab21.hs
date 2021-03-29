natural::Integer -> [Integer] --1
natural 1 = [1]
natural n = natural (n-1) ++ [n]

natodd::Integer -> [Integer] --2
natodd 1 = [1]
natodd n = natodd (n-1) ++ [n*2-1]

nateven::Integer -> [Integer] --3
nateven 1 = [0]
nateven n = nateven (n-1) ++ [n*2]

square::Int -> [Int] --4
square 1 = [1]
square n = square (n-1) ++ [n*n]

factorial::Int -> [Int] --5
factorial 0 = [1]
factorial 1 = [1]
factorial n = f ++ [(last f)*n] where f=factorial (n-1)

square2::Int -> [Int] --6
square2 1 = [2]
square2 n = square2 (n-1) ++ [2^n]

triangle::Int -> [Int] --7
triangle 1 = [1]
triangle n = t1 ++ [(last t1)+n] where t1=triangle (n-1)

pyramid::Int -> [Int] --8
pyramid 1 = [1]
pyramid n = p ++ [(last p)+(last t2)] where p=pyramid (n-1); t2=triangle n