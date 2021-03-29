import System.Environment

main = do
         args <- getArgs
         putStrLn "Your arguments is:"
         mapM putStrLn args