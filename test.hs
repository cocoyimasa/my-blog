accum :: [Char] -> Int -> [Char]
accum x 0 = ""
accum x n = x ++ accum x (n-1)
