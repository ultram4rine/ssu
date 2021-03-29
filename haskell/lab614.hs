import System.IO
import System.Environment

main = do --take берет первые n элементов списка
         (n:filename:etc) <- getArgs
         handle <- openFile filename ReadMode
         content <- hGetContents handle
         putStrLn "First n strings of file is:"
         mapM putStrLn (take (read n) (lines content))
         hClose handle
         