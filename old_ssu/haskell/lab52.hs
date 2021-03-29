type StringFunc = String -> String

clean :: String -> String
clean _ = ""

delete :: Char -> String -> String
delete x = filter(/=x)

replace :: Char -> Char -> String -> String
replace y z = map(\x -> (if x==y then z else x))

insert :: Char -> String -> String
insert = (:)

process :: StringFunc -> String -> String
process = ($)

processAll :: [StringFunc] -> String -> String
processAll = flip(foldl(flip ($)))

deleteAll :: String -> String -> String
deleteAll = processAll . map delete