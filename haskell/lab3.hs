{-# LANGUAGE ViewPatterns #-}

data String7 a = Conv (String -> String)

clean :: String7 a -> String
clean _ = "";

--delete :: Char -> String -> String;
--delete x = filter(/=x);

--replace :: Char->Char->String->String;
--replace pat1 pat2 = map (\x -> (if x==pat1 then pat2 else x));

--adding :: Char -> String -> String;
--adding = (:);

--process :: (String7 a -> a) -> String -> String;
--process = id

--processAll :: [String -> String] -> String -> String;
--processAll = flip(foldl (flip id))

--deleteAll :: String -> String -> String;
--deleteAll = processAll . map delete






