import System.IO
import System.Environment

main = do
         (filename:etc) <- getArgs
         handle <- openFile filename ReadMode
         content <- hGetContents handle
         putStrLn "Your file is:"
         putStrLn content
         hClose handle