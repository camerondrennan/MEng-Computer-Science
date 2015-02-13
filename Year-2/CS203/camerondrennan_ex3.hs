--Ex1
data Nat = Zero | Suc Nat 
     deriving (Show,Eq)

type PosQ = (Nat,Nat)

myadd:: Nat->Nat->Nat
myadd Zero x = x
myadd (Suc x) y = Suc (myadd x y)


--(a)
mymult::Nat -> Nat -> Nat
mymult (Zero) (x) = Zero
mymult (Suc x) y = myadd y (mymult x y)



--(b) 
fraceq::PosQ -> PosQ -> Bool
fraceq x y = if fromInteger(natToInt ((fst x))) / fromInteger(natToInt ((snd x))) == fromInteger(natToInt ((fst y))) / fromInteger(natToInt ((snd y))) 
				then True 
				else False

natToInt :: Nat -> Integer
natToInt Zero = 0
natToInt (Suc n) = 1 + natToInt n


--Ex2
type Position = (Int,Int)
data Step = L | R | U | D

--(a) 
move::Step->Position->Position
move (L) input = ((fst input) - 1, snd input)
move (R) input = ((fst input) + 1, snd input)
move (U) input = (fst input, (snd input) + 1)
move (D) input = (fst input, (snd input) - 1)

--(b)
type Route = [Step]

positions::Route -> Position->[Position]
positions route initialPos 
						| length route > 1 = newPos : positions (drop 1 route) newPos
						| otherwise = [newPos]
						where
						newPos = move(head route) initialPos

--(c) 
equiv :: Route -> Route -> Bool
equiv fstR sndR = if last (positions fstR (0,0)) == last (positions sndR (0,0))
					then True
					else False


--Ex3
data BTree a = Leaf a | Node a (BTree a) (BTree a)
     deriving (Show,Eq)

testtree1 = Node 5 (Node 4 (Leaf 1) (Leaf 2)) (Node 3 (Leaf 3) (Leaf 4))
testtree2 = Node 3 (Leaf 76) (Node 3 (Leaf 8) (Leaf 9))


--(a)
treesum :: Num a => BTree a -> a 
treesum (Leaf x) = x
treesum (Node x l r) = treesum l + x + treesum r

--(b)
paths :: BTree a -> [[a]] 
paths (Leaf x) = [[x]]
paths (Node x l r) = do
					t <- [l, r]
					map (x:) (paths t)