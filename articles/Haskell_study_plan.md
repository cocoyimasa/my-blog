## Haskell Study Plan
Note : Parentheses ( ), Brackets [ ], and Braces { } 
Basic code area

```haskell
-- Single line comment

{- Multiple line comment -}

-- check type signature
:type

-- if-else and list comprehension
[if x==0  then x else 1 | x <- [1,2,3,4,5,6]]

-- map
map :: (a -> b) -> [a] -> [b]

-- filter
filter :: (a -> Bool) -> [a] -> [a]

-- foldr,foldl

-- zip
zip :: [a] -> [b] -> [(a, b)]
zip [1,2,3] [4,5,6] -- result:[(1,4),(2,5),(3,6)]

-- lambda calculas
(\x y -> x+y)

-- ++ : combine string or list
[1,2,3]++[4,5,6] -- result: [1,2,3,4,5,6]
"sss"++"111" -- "sss111"

-- : combine list
1:[2,3] -- [1,2,3]

-- guard expression, (x:xs) the parentheses are necessary.
func :: [Int] -> Int
func (x:xs) 
  | x==1 = 0 
  | otherwise = x
  
-- isUpper, isLower, toUpper, toLower
toUpper 'a' -- 'A'
toLower 'A' -- 'a'
isLower 'a' -- True
isUpper 'a' -- False

-- char to ascii, (import Data.Char)
ord :: Char -> Int  
ord 'a' -- result: 97

-- pattern matching
case sort [a,b,c] of [x,y,z] -> (x + y ) > z

-- sort ,(import Data.List)
sort [2,1,3] -- [1,2,3]

-- reverse ,(import Data.List)
reverse [1,2,3] -- [3,2,1]

```
