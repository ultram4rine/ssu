data Number = Zero | Next Number deriving (Eq, Show)

fromInt :: Int -> Number
fromInt 0 = Zero
fromInt a = Next (fromInt (a-1))

toInt :: Number -> Int
toInt Zero = 0
toInt (Next a) = 1+(toInt (a))

plus :: Number -> Number -> Number
plus a b = fromInt(toInt(a)+toInt(b))

mult :: Number -> Number -> Number
mult a b = fromInt(toInt(a)*toInt(b))

dec :: Number -> Number
dec Zero = Zero
dec a = fromInt(toInt(a)-1)

fact :: Number -> Number
fact Zero = Next Zero
fact a = fromInt(toInt(a)*toInt(fact(fromInt(toInt(a)-1))))