(echo a | (echo b1 || echo b2 | echo b3 | echo b4) ; (echo c1; (echo c11 && echo c12) && echo d))
