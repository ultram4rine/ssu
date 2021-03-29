import System.IO

str2int :: String -> Int
str2int x = (read x) :: Int

main = do
         putStrLn "Enter x:"
         sx <- getLine
         putStrLn "Enter y:"
         sy <- getLine
         putStrLn $ "x+y=" ++ (show $ (str2int sx)+(str2int sy))