tmopow::Integral a => a -> a --5
tmopow 1 = 2
tmopow n = if even n then tmopow((quot n 2))*tmopow((quot n 2))
                     else tmopow((quot (n-1) 2))*tmopow((quot (n-1) 2))*2

removeEmpty::[String] -> [String] --7
removeEmpty [] = []
removeEmpty (x:xs) | isEmptyStr x = removeEmpty xs
                   | otherwise = x : removeEmpty xs
                   where isEmptyStr [] = True
                         isEmptyStr (' ':ys) = isEmptyStr ys
                         isEmptyStr _ = False
