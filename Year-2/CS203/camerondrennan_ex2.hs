import Data.Char
import Data.List
 
stringdub :: String -> String
stringdub str = concatMap (replicate 2) str
				
intLog :: Int->Int->Int
intLog n d = if d < n then 0       
			else let
			l = 2 * intLog (n*n) d
			doDiv d l = if d < n then l else doDiv (d`div`n) (l+1)
			in
			doDiv (d`div`(n^l)) l

fib :: [Int]
fib = 1:1:zipWith (+) fib (tail fib)
 

scalarprod :: [Int] -> [Int] -> Int
scalarprod xs ys = if length xs == length ys
					then sum [x * y | (x, y) <- zip xs ys]
					else error"Lists are not of an equal length"