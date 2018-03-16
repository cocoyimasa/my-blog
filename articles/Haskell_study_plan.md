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

-- 喵的，还是用中文吧。。。。。。。

-- read类似js的eval，只不过Haskell是强类型，此处需要指定返回类型
-- if..then..else,else部分不可以省略
[if x>0 then x else 0 | x <- (read "[1,2,3,4]"::[Int])]
read "5" :: Int
read "[1,2,3,4]"::[Int]
-- :type 可缩写为 :t,查看一个运算符的类型，需要加括号
:type ($)

-- guard，where
func w h
| x <= 10.0 = "!"
| x <= 20.0 = "!!"
| x <= 30.0 = "!!!"
| otherwise = "- -"
where x = w / h ^ 2 --局部变量
      (s, n, f) = (18.0, 20.0, 30.0) -- where里面的模式匹配
      
--let..in let..in和guard..where类似，但let中是声明，in里是计算
func r h =
   let a = 2 * pi
     b = 1
   in  a + 2 * b 

-- 右折叠  
foldr :: (a -> b -> b) -> b -> [a] -> b  
foldr f acc []     = acc  
foldr f acc (x:xs) = f x (foldr f acc xs)  
-- foldr f acc [a, b, c, d] = f a (f b (f c (f d acc)))  
-- foldr f acc [a, b, c, d] = a `f` (b `f` (c `f` (d `f` acc)))  

-- 左折叠  
foldl :: (a -> b -> a) -> a -> [b] -> a  
foldl f acc []     =  acc  
foldl f acc (x:xs) =  foldl f (f acc x) xs  
-- foldl f acc [a, b, c, d] = f (f (f (f acc a) b) c) d  
-- foldl f acc [a, b, c, d] = (((acc `f` a) `f` b) `f` c) `f` d  


```
