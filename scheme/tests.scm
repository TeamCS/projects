;;; Test cases for Scheme.
;;;
;;; In order to run only a prefix of these examples, add the line
;;;
;;; (exit)
;;;
;;; after the last test you wish to run.

;;; Additional tests
;;;
;;; **********************************
;;; *** Add more of your own here! ***
;;; **********************************

;;; Question 1
;;; Question 2
;;; Question 3
;;; Question 4

;;; None

;;; Question 5

(define pi 3.1415926)
; expect pi
 
(define lin (* 333 (+ 1 1)))
; expect lin

(define alan 'lin)
; expect alan

pi
; expect 3.1415926

lin
; expect 666

alan
; expect lin

(define pi 3.14)
; expect pi

pi
; expect 3.14

(/ lin 6)
; expect 111

(define a 1 2)
; expect Error: too many operands in form

(define 'a 2)
; expect quote

(define 1 2)
; expect Error: bad argument to define

(define '(hello) 1)
; expect Error: not a symbol: (hello)

(define lst '(1))
; expect lst

lst
; expect (1)

(define lst2 '(2 . 3))
lst2
; expect (2 . 3)

;;; Question 6

'lin
; expect lin

'(+ 1 2)
; expect (+ 1 2)

'(1 (lin pi))
; expect (1 (lin pi))

'(1 'lin)
; expect (1 (quote lin))

(cons '(1 2) '(lin))
; expect ((1 2) lin)

(cons '(lin) 2)
; expect ((lin) . 2)

'((1 2) . (3 4))
; expect ((1 2) 3 4)

'((1 2) . 3)
; expect ((1 2) . 3)

;;; Question 7

(begin lin (* 333 1))
; expect 333

(begin (define ha 7) (define x 6))
; expect x

ha
; expect 7

(begin 1 lin)
; expect 666

(begin 1)
; expect 1

(begin False '(1 2))
; expect (1 2)

(begin)
; expect Error: too few operands in form

(+ 1 (begin 1 2))
; expect 3

(begin (define x 1) (+ x 1))
; expect 2

(begin (define y 2) (list y 1))
; expect (2 1)

;;; Question 8

(lambda)
; expect Error: too few operand in form

(lambda (a b) (* a b))
; expect (lambda (a b) (* a b))

(define x (lambda (a b) (* a b)))
; expect x

(x 1 2)
; expect 2

((lambda (a b) (define ab 1) (+ ab b)) 2 3)
; expect 4

(lambda ('x) 1)
; expect Error: not a symbol: (quote x)

(lambda x)
; expect Error: too few operands in form

(lambda (x) 1 2)
; expect (lambda (x) (begin 1 2))

(lambda 1 2)
; expect Error

(lambda (x 1) 1)
; expect Error: not a symbol: 1

;;; Question 9

(define (square x) (* x x))
; expect square

(square 2)
; expect 4

(define (triple-add x y z) (* 3 (+ x y z)))
; expect triple-add

(triple-add 1 2 3)
; expect 18

(define (double-double x) (define double (* 2 x)) (* 2 double))
; expect double-double

(double-double 2)
; expect 8

(define (6 x y) (+ x y))
; expect Error: bad argument to define

(define (f 'a 'b) 1)
; expect Error: not a symbol: (quote a)

(define (f) 1)
; expect f

f
; expect (lambda () 1)

(define (m))
; expect Error: too few operands in form

;;; Question 10

;;; None

;;; Question 11

;;; Included in Q9

;;; Question 12

(define (triple x) (* 3 x))
(triple 3)
; expect 9

(define (foo x) (define (bar y) (+ x y)) (bar 4))
(foo 1)
; expect 5

(define (foo x) (define (bar y) (+ x y)) bar)
((foo 1) 4)
; expect 5

;;; Question 13

(if)
; expect Error: too few operands in form

(if (eq? 1 1))
; expect Error: too few operands in form

(if (eq? 1 1) 1)
; expect 1

(if (eq? 1 2) 1)
; expect okay

(if 1 1 2)
; expect 1

(if '(1 2) 1 2)
; expect 1

(if (eq? 1 2) (define nihao 1) (eq? 1 2))
; expect False

nihao
; expect Error: Unknown identifier

(if (eq? 1 1) 1 2 3)
; expect Error: too many operands in form

(if (eq? 1 2) (/ 1 0) 5)
; expect 5

(if (eq? 1 2) 1 (/ 1 0))
; expect Error: division by zero

(if (eq? 3 4) (square 2) (* 5 6))
; expect 30

(if (eq? 5 6) (/ 1 0))
; expect okay

(if (eq? 3 3) '(1 . 2) 1)
; expect (1 . 2)

;;; Question 14

(and)
; expect True

(and (/ 1 0) 5)
; expect Error: divison by zero

(and (eq? 3 4) (/ 1 0))
; expect False

(and (define z 2) (define z (+ z 1)) z)
; expect 3

(and (eq? 1 2) (define test 1))
; expect False

test
; expect Error: Unknown identifier

(or)
; expect False

(or 4 (/ 1 0))
; expect 4

(or (define z 2) (define z (+ z 1)) z)
; expect z

(or '(1) (define test 1))
; expect (1)

test
; expect Error: Unknown identifier

(define test 1)
(or test 2)
; expect 1

(define (test x) (+ x 1))
(or test 2)
; expect (lambda (x) (+ x 1))

;;; Question 15

(cond)
; expect okay

(cond ((eq? 1 2) 1)
	  ((eq? 3 3) lin))
; expect 666

(cond ((eq? 3 3) (define x 1) (define x (+ x 1)) x))
; expect 2

(cond ((eq? 3 4) 'abc) ('hello))
; expect hello

(cond ((eq? 3 3)))
; expect True

(cond ('(1 2 3)))
; expect (1 2 3)

(cond (else))
; expect Error: badly formed else clause

(cond ((= 1 2) 1)
	  1)
; expect Error: badly formed expression: 1

(cond ((= 1 2) 1) (1))
; expect 1

(cond (else 1))
; expect 1

(cond ((eq? 1 1) 1) 
	  ((eq? 1 1) (define test15 1)))
; expect 1

test15
; expect Error: Unknown Identifier

;;; Question 16

(let)
; expect Error: too few operands in form

(let ((x 42)) x 1 2)
; expect 2

(let ((lin 123)) lin)
; expect 123

(let ((1 2)) 2)
; expect Error

(let 2)
; expect Error

(let ((x 1 2)) x)
; expect Error

(let 1 2)
; expect Error

(let (1) 1)
; expect Error

(let ((x 1 2)) x)
; expect Error

(let ((x (* 5 (+ 2 3)))) x)
; expect 25

(let ((x (lambda (x) (+ x 1)))) (x 1))
; expect 2

(let ((test16 1)) test16)
; expect 1

test16
; expect Error: Unknown Identifier

;;; Question 17

(define f (mu (1) (* m n)))
; expect Error

(define g (mu (x y) (+ x y) 1))
(g 1 2)
; expect 1

;;; Scheme implementation tests

(define (factorial x)
  (if (eq? x 1)
      1
	  (* x
	     (factorial (- x 1)))))
		 
(factorial 5)
; expect 120
		 
(define (fib n)
    (if (< n 2)
	    1
		(+ (fib (- n 1))
		   (fib (- n 2)))))
		   
(fib 5)
; expect 8
		   
(define (map fn lst)
	(if (null? lst)
		nil
		(cons (fn (car lst))
			  (map fn (cdr lst)))))
			  
(map (lambda (x) (+ x 1)) '(1 2 3 4))
; expect (2 3 4 5)
			  
(define (reduce fn s lst)
	(if (null? lst)
		s
		(fn (car lst)
			(reduce fn s (cdr lst)))))

(reduce (lambda (x y) (+ x y)) 0 '(1 2 3 4))			
; expect 10
		   
(define (insert elem lst position)
	(if (= position 0)
		(cons elem lst)
		(cons (car lst) (insert elem (cdr lst) (- position 1)))))
		
(insert 5 '(1 2 3 4) 4)
; expect (1 2 3 4 5)
		
(define (duplicate lst)
	(if (null? lst)
		nil
		(cons (car lst) (cons (car lst) (duplicate (cdr lst))))))

(duplicate '(1 2 3))		
; expect (1 1 2 2 3 3)

(define empty nil)

(define (make-btree entry left right)
	(cons entry (cons left right)))
	
(define (entry tree)
	(car tree))
	
(define (left tree)
	(car (cdr tree)))
	
(define (right tree)
	(cdr (cdr tree)))
	
(define (btree-sum tree)
	(if (null? tree)
		0
		(+ (entry tree)
		   (btree-sum (left tree))
		   (btree-sum (right tree)))))
		   
(btree-sum (make-btree 3 
					   (make-btree 2 empty empty) 
					   (make-btree 1 empty empty)))
; expect 6

;;; Tail call optimization
(define (identity x n)
		(if (eq? x 0)
			n
			(identity (- x 1)
					  (+ n 1))))
			
(identity 6000 0)
; expect 6000

;;; These are examples from several sections of "The Structure
;;; and Interpretation of Computer Programs" by Abelson and Sussman.

;;; License: Creative Commons share alike with attribution

;;; 1.1.1

10
; expect 10

(+ 137 349)
; expect 486

(- 1000 334)
; expect 666

(* 5 99)
; expect 495

(/ 10 5)
; expect 2

(+ 2.7 10)
; expect 12.7

(+ 21 35 12 7)
; expect 75

(* 25 4 12)
; expect 1200

(+ (* 3 5) (- 10 6))
; expect 19

(+ (* 3 (+ (* 2 4) (+ 3 5))) (+ (- 10 7) 6))
; expect 57

(+ (* 3
      (+ (* 2 4)
         (+ 3 5)))
   (+ (- 10 7)
      6))
; expect 57

;;; 1.1.2

(define size 2)
; expect size
size
; expect 2

(* 5 size)
; expect 10

(define pi 3.14159)
(define radius 10)
(* pi (* radius radius))
; expect 314.159

(define circumference (* 2 pi radius))
circumference
; expect 62.8318

;;; 1.1.4

(define (square x) (* x x))
; expect square
(square 21)
; expect 441

(define square (lambda (x) (* x x))) ; See Section 1.3.2
(square 21)
; expect 441

(square (+ 2 5))
; expect 49

(square (square 3))
; expect 81

(define (sum-of-squares x y)
  (+ (square x) (square y)))
(sum-of-squares 3 4)
; expect 25

(define (f a)
  (sum-of-squares (+ a 1) (* a 2)))
(f 5)
; expect 136

;;; 1.1.6

(define (abs x)
  (cond ((> x 0) x)
        ((= x 0) 0)
        ((< x 0) (- x))))
(abs -3)
; expect 3

(abs 0)
; expect 0

(abs 3)
; expect 3

(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))
(a-plus-abs-b 3 -2)
; expect 5

;;; 1.1.7

(define (sqrt-iter guess x)
  (if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x)
                 x)))
(define (improve guess x)
  (average guess (/ x guess)))
(define (average x y)
  (/ (+ x y) 2))
(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.001))
(define (sqrt x)
  (sqrt-iter 1.0 x))
(sqrt 9)
; expect 3.00009155413138

(sqrt (+ 100 37))
; expect 11.704699917758145

(sqrt (+ (sqrt 2) (sqrt 3)))
; expect 1.7739279023207892

(square (sqrt 1000))
; expect 1000.000369924366

;;; 1.1.8

(define (sqrt x)
  (define (good-enough? guess)
    (< (abs (- (square guess) x)) 0.001))
  (define (improve guess)
    (average guess (/ x guess)))
  (define (sqrt-iter guess)
    (if (good-enough? guess)
        guess
        (sqrt-iter (improve guess))))
  (sqrt-iter 1.0))
(sqrt 9)
; expect 3.00009155413138

(sqrt (+ 100 37))
; expect 11.704699917758145

(sqrt (+ (sqrt 2) (sqrt 3)))
; expect 1.7739279023207892

(square (sqrt 1000))
; expect 1000.000369924366

;;; 1.3.1

(define (cube x) (* x x x))
(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))
(define (inc n) (+ n 1))
(define (sum-cubes a b)
  (sum cube a inc b))
(sum-cubes 1 10)
; expect 3025

(define (identity x) x)
(define (sum-integers a b)
  (sum identity a inc b))
(sum-integers 1 10)
; expect 55

;;; 1.3.2

((lambda (x y z) (+ x y (square z))) 1 2 3)
; expect 12

(define (f x y)
  (let ((a (+ 1 (* x y)))
        (b (- 1 y)))
    (+ (* x (square a))
       (* y b)
       (* a b))))
(f 3 4)
; expect 456

(define x 5)
(+ (let ((x 3))
     (+ x (* x 10)))
   x)
; expect 38

(let ((x 3)
      (y (+ x 2)))
  (* x y))
; expect 21

;;; 2.1.1

(define (add-rat x y)
  (make-rat (+ (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))
(define (sub-rat x y)
  (make-rat (- (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))
(define (mul-rat x y)
  (make-rat (* (numer x) (numer y))
            (* (denom x) (denom y))))
(define (div-rat x y)
  (make-rat (* (numer x) (denom y))
            (* (denom x) (numer y))))
(define (equal-rat? x y)
  (= (* (numer x) (denom y))
     (* (numer y) (denom x))))

(define x (cons 1 2))
(car x)
; expect 1

(cdr x)
; expect 2

(define x (cons 1 2))
(define y (cons 3 4))
(define z (cons x y))
(car (car z))
; expect 1

(car (cdr z))
; expect 3

z
; expect ((1 . 2) 3 . 4)

(define (make-rat n d) (cons n d))
(define (numer x) (car x))
(define (denom x) (cdr x))
(define (print-rat x)
  (display (numer x))
  (display '/)
  (display (denom x))
  (newline))
(define one-half (make-rat 1 2))
(print-rat one-half)
; expect 1/2 ; okay

(define one-third (make-rat 1 3))
(print-rat (add-rat one-half one-third))
; expect 5/6 ; okay

(print-rat (mul-rat one-half one-third))
; expect 1/6 ; okay

(print-rat (add-rat one-third one-third))
; expect 6/9 ; okay

(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))
(define (make-rat n d)
  (let ((g (gcd n d)))
    (cons (/ n g) (/ d g))))
(print-rat (add-rat one-third one-third))
; expect 2/3 ; okay

(define one-through-four (list 1 2 3 4))
one-through-four
; expect (1 2 3 4)

(car one-through-four)
; expect 1

(cdr one-through-four)
; expect (2 3 4)

(car (cdr one-through-four))
; expect 2

(cons 10 one-through-four)
; expect (10 1 2 3 4)

(cons 5 one-through-four)
; expect (5 1 2 3 4)

(define (map proc items)
  (if (null? items)
      nil
      (cons (proc (car items))
            (map proc (cdr items)))))
(map abs (list -10 2.5 -11.6 17))
; expect (10 2.5 11.6 17)

(map (lambda (x) (* x x))
     (list 1 2 3 4))
; expect (1 4 9 16)

(define (scale-list items factor)
  (map (lambda (x) (* x factor))
       items))
(scale-list (list 1 2 3 4 5) 10)
; expect (10 20 30 40 50)

(define (count-leaves x)
  (cond ((null? x) 0)
        ((not (pair? x)) 1)
        (else (+ (count-leaves (car x))
                 (count-leaves (cdr x))))))
(define x (cons (list 1 2) (list 3 4)))
(count-leaves x)
; expect 4

(count-leaves (list x x))
; expect 8

;;; 2.2.3

(define (odd? x) (= 1 (remainder x 2)))
(define (filter predicate sequence)
  (cond ((null? sequence) nil)
        ((predicate (car sequence))
         (cons (car sequence)
               (filter predicate (cdr sequence))))
        (else (filter predicate (cdr sequence)))))
(filter odd? (list 1 2 3 4 5))
; expect (1 3 5)

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))
(accumulate + 0 (list 1 2 3 4 5))
; expect 15

(accumulate * 1 (list 1 2 3 4 5))
; expect 120

(accumulate cons nil (list 1 2 3 4 5))
; expect (1 2 3 4 5)

(define (enumerate-interval low high)
  (if (> low high)
      nil
      (cons low (enumerate-interval (+ low 1) high))))
(enumerate-interval 2 7)
; expect (2 3 4 5 6 7)

(define (enumerate-tree tree)
  (cond ((null? tree) nil)
        ((not (pair? tree)) (list tree))
        (else (append (enumerate-tree (car tree))
                      (enumerate-tree (cdr tree))))))
(enumerate-tree (list 1 (list 2 (list 3 4)) 5))
; expect (1 2 3 4 5)

;;; 2.3.1

(define a 1)

(define b 2)

(list a b)
; expect (1 2)

(list 'a 'b)
; expect (a b)

(list 'a b)
; expect (a 2)

(car '(a b c))
; expect a

(cdr '(a b c))
; expect (b c)

(define (memq item x)
  (cond ((null? x) false)
        ((eq? item (car x)) x)
        (else (memq item (cdr x)))))
(memq 'apple '(pear banana prune))
; expect False

(memq 'apple '(x (apple sauce) y apple pear))
; expect (apple pear)

(define (equal? x y)
  (cond ((pair? x) (and (pair? y)
                        (equal? (car x) (car y))
                        (equal? (cdr x) (cdr y))))
        ((null? x) (null? y))
        (else (eq? x y))))
(equal? '(1 2 (three)) '(1 2 (three)))
; expect True

(equal? '(1 2 (three)) '(1 2 three))
; expect False

(equal? '(1 2 three) '(1 2 (three)))
; expect False

;;; Peter Norvig tests (http://norvig.com/lispy2.html)

(define double (lambda (x) (* 2 x)))
(double 5)
; expect 10

(define compose (lambda (f g) (lambda (x) (f (g x)))))
((compose list double) 5)
; expect (10)

(define apply-twice (lambda (f) (compose f f)))
((apply-twice double) 5)
; expect 20

((apply-twice (apply-twice double)) 5)
; expect 80

(define fact (lambda (n) (if (<= n 1) 1 (* n (fact (- n 1))))))
(fact 3)
; expect 6

(fact 50)
; expect 30414093201713378043612608166064768844377641568960512000000000000

(define (combine f)
  (lambda (x y)
    (if (null? x) nil
      (f (list (car x) (car y))
         ((combine f) (cdr x) (cdr y))))))
(define zip (combine cons))
(zip (list 1 2 3 4) (list 5 6 7 8))
; expect ((1 5) (2 6) (3 7) (4 8))

(define riff-shuffle (lambda (deck) (begin
    (define take (lambda (n seq) (if (<= n 0) (quote ()) (cons (car seq) (take (- n 1) (cdr seq))))))
    (define drop (lambda (n seq) (if (<= n 0) seq (drop (- n 1) (cdr seq)))))
    (define mid (lambda (seq) (/ (length seq) 2)))
    ((combine append) (take (mid deck) deck) (drop (mid deck) deck)))))
(riff-shuffle (list 1 2 3 4 5 6 7 8))
; expect (1 5 2 6 3 7 4 8)

((apply-twice riff-shuffle) (list 1 2 3 4 5 6 7 8))
; expect (1 3 5 7 2 4 6 8)

(riff-shuffle (riff-shuffle (riff-shuffle (list 1 2 3 4 5 6 7 8))))
; expect (1 2 3 4 5 6 7 8)

;;; Additional tests

(apply square '(2))
; expect 4

(apply + '(1 2 3 4))
; expect 10

(apply (if false + append) '((1 2) (3 4)))
; expect (1 2 3 4)

(if 0 1 2)
; expect 1

(if '() 1 2)
; expect 1

(or false true)
; expect True

(or)
; expect False

(and)
; expect True

(or 1 2 3)
; expect 1

(and 1 2 3)
; expect 3

(and False (/ 1 0))
; expect False

(and True (/ 1 0))
; expect Error

(or 3 (/ 1 0))
; expect 3

(or False (/ 1 0))
; expect Error

(or (quote hello) (quote world))
; expect hello

(if nil 1 2)
; expect 1

(if 0 1 2)
; expect 1

(if (or false False #f) 1 2)
; expect 2

(define (loop) (loop))
(cond (false (loop))
      (12))
; expect 12

((lambda (x) (display x) (newline) x) 2)
; expect 2 ; 2

(define g (mu () x))
(define (high f x)
  (f))

(high g 2)
; expect 2

(define (print-and-square x)
  (print x)
  (square x))
(print-and-square 12)
; expect 12 ; 144

(/ 1 0)
; expect Error

(define addx (mu (x) (+ x y)))
(define add2xy (lambda (x y) (addx (+ x x))))
(add2xy 3 7)
; expect 13


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Scheme Implementations ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; len outputs the length of list s
(define (len s)
  (if (eq? s '())
    0
    (+ 1 (len (cdr s)))))
(len '(1 2 3 4))
; expect 4


;;;;;;;;;;;;;;;;;;;;
;;; Extra credit ;;;
;;;;;;;;;;;;;;;;;;;;



; Tail call optimization test
(define (sum n total)
  (if (zero? n) total
    (sum (- n 1) (+ n total))))
(sum 1001 0)
; expect 501501
