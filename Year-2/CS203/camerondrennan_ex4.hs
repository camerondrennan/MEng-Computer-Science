--- help functions

intlog::Integer -> Integer -> Integer
intlog n d 
       | d <= 1 = error "second argument of intlog needs to be bigger than 1"
       | mod n d /= 0 = 0
       | otherwise = intlog (div n d) d + 1

--Ex1
rev :: [a] -> [a]
rev xs = foldl i [] xs
			where i acc b = b : acc

--Ex2
--(a)
insert :: Ord b => (a -> b) -> a -> [a] -> [a]
insert a b [] = [b]
insert a b (x:xs)
    | a b <= a x = b : x : xs
    | otherwise  = x : insert a b xs

--(b) 
inssort :: Ord b => (a -> b) -> [a] -> [a]
inssort a [] = []
inssort a (x:xs) = insert a x (inssort a xs)

--(c)
countocc :: Char -> String -> Int
countocc a = foldr (\x count -> if x == a 
									then count+1 
									else count) 0

--(d) Order a list of strings according to length
sortwords :: Char -> [String] -> [String]
sortwords = undefined
--sortwords a = sortBy (\xs ys -> compare (countocc a) (countocc a))

--Ex3
--(a)
cutoffat:: Eq a => a -> [a] -> [a]
cutoffat = undefined

--(b) 
collatzdist::Integer -> Integer 
collatzdist = undefined


--Ex4
--(a)
primes :: [Integer]
primes = sieve [2..]
			where sieve (a:xs) = a : sieve [x|x <- xs, x `mod` a > 0]

--(b)
primefact :: Integer -> [(Integer,Integer)]
primefact = undefined

--(c) 
mygcd :: Integer -> Integer -> Integer
mygcd x y
      | (x<0 || y <0) = 0
      | otherwise = undefined