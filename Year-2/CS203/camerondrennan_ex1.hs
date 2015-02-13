import Data.Char

myisDigit :: Char -> Bool
myisDigit c =  c >= '0' && c <= '9'				

offset :: Int
offset = ord 'A' - ord 'a'

mytoUpper :: Char -> Char
mytoUpper ch = if ord ch >= ord 'a'
				then (chr (ord ch + offset))
				else ch

roots :: Float -> Float -> Float -> (Float,Float)        
roots a b c = if a == 0
				then error "Needs to be quadratic equation"
				else 
					if d < 0 then error "0" else (x, y)
                        where
							d = b * b - 4 * a * c
							e = - b / (2 * a)
							x = e + sqrt d / (2 * a)
							y = e - sqrt d / (2 * a)

compLetters :: Char -> Char -> Char						  
compLetters a b = if (mytoUpper a) <= (mytoUpper b)
					then a
					else b	
