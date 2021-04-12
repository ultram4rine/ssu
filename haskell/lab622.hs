import System.IO
import System.Environment

str2int :: String -> Int
str2int x = (read x) :: Int

main = do
         putStrLn "Enter first coordinate of first circle:"
         x1 <- getLine
         putStrLn "Enter second coordinate of first circle:"
         y1 <- getLine
         putStrLn "Enter first coordinate of second circle:"
         x2 <- getLine
         putStrLn "Enter second coordinate of second circle:"
         y2 <- getLine
         putStrLn "Enter first radius:"
         r1 <- getLine
         putStrLn "Enter second radius:"
         r2 <- getLine
         if ((str2int x2)-(str2int x1))*((str2int x2)-(str2int x1)) + ((str2int y2)-(str2int y1))*((str2int y2)-(str2int y1))<((str2int r2)-(str2int r1))*((str2int r2)-(str2int r1))
                                  then putStrLn "True"
                                  else putStrLn "False"
