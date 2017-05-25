#lang racket
;************************************
;~~~~~~~~~~~~Project 3~~~~~~~~~~~~~~~
;************************************
(printf "-----------\n Project 3\n-----------\n\n")



;------------------------------
;       List Functions
;------------------------------
(printf "LIST FUNCTIONS:\n\n")

;_______________
;    Choice 1
; Append two lists
(printf "1. Append two Lists:\n")

;Lists used
(define list1 (list 1 3 9 8))
(define list2 (list 4 2 6))
(define list3 (list))
(define list4 (list))

;Define function myappend
(define (myappend lis1 lis2)
  (cond
    ((null? lis2) lis1) ;If list2 is empty, end recursion
    ((null? lis1) (cons (car lis2) (myappend lis1 (cdr lis2)))) ;If lis1 is empty, do lis2
    (else (cons (car lis1) (myappend (cdr lis1) lis2))))) ;If lis1 is not empty, add lis1

;Test cases
(myappend list1 list2)
(myappend list3 list4)


;_______________
;    Choice 2
; Reverse a list
(printf "2. Reverse a List:\n")

;Lists used
(define listRev1 (list 1 3 9 8))
(define listRev2 (list 4 2 6))

;Define function myreverse
(define (myreverse lis1)
  (cond
    ((null? lis1) lis1) ;If lis1 empty, return lis1
    ;else get last character and add to beggining of new list to return
    (else (cons (last lis1) (myreverse (take lis1 (- (length lis1) 1)))))))

;Test cases
(myreverse listRev1)
(myreverse listRev2)
(myreverse list3)


;_______________
;    Choice 4
; Remove duplicates from a list
(printf "4. Remove duplicates from a List:\n")

;Lists used
(define listDups (list 1 1 2 4 1 2 5))
(define listDups2 (list 2 3 4 4 4 5 1 6 7 2 2))
(define finalLis (list))

;Define functions for mynub
(define (setFinalList2 list1 elem)
  (set! finalLis (list* elem list1))
  )

(define (setFinalList1 list1)
  (set! finalLis list1)
  )

(define (mynub lis1)
  (setFinalList1 (list))
  ;Go through the list and check if it is a member of another, remove if so
  (map (lambda (elem)
         (if (member elem finalLis) (remove elem lis1) (setFinalList2 finalLis elem))) 
         lis1)
  (myreverse finalLis))

;Test cases
(mynub listDups)
(mynub listDups2)

;_______________
;    Choice 8
; Add to End
(printf "8. Add an element to end of List:\n")

;Lists used
(define listAddtoEnd (list 2 5 6 7))
(define listAddtoEnd2 (list 5 1 6 7 2 2))

;Define Function
(define (myaddtoend elem lis1)
  ;Reverse the list, add to front, and reverse the list again to add to end
  (myreverse (list* elem (myreverse lis1))))

;Test cases
(myaddtoend 6 listAddtoEnd)
(myaddtoend 10 listAddtoEnd2)

;_______________
;    Choice 9
;    Index Of
(printf "9. Index Of:\n")

;Lists used
(define indexof (list 2 5 6 7))
(define indexof2 (list 2 9 3 4))
(define indexof3 (list 5 8 1 7 2))
(define indexof4 (list 1 9 8 2 2 3))

;Define Function
(define (myindexof elem lis1)
  ;If empty list return -1
  (if (null? lis1) -1 (myindexof-helper elem lis1 0)))

(define (myindexof-helper elem lis1 count)
  ;While count is less then length, check if element at count is equal to element checking for
  ;and react accordingly. If count gets to the length of list, return -1.
  (if (< count (length lis1))
      (if (equal? elem (list-ref lis1 count)) count (myindexof-helper elem lis1 (+ 1 count)))
      -1)
  )

;Test cases
(myindexof 6 indexof) ;Should be 2
(myindexof 2 indexof2) ;Should be 0
(myindexof 9 indexof3) ;Should be -1
(myindexof 3 indexof4) ;Should be 5

;_______________
;    Choice 10
; Remove-all
(printf "10. Remove-all:\n")

;Lists used
(define removeAll (list 2 5 6 7 1 9))
(define removeAll2 (list 5 1 6 7 2 2 2))
(define removeAll3 (list 5 8 6 7 8 8 8))

;Define Function
(define (myremoveall elem lis1)
  ;Recursively continue to remove elements until all of the type of element are gone
  (if (member elem lis1)
      (myremoveall elem (remove elem lis1))
      lis1)
  )

;Test cases
(myremoveall 6 removeAll)
(myremoveall 2 removeAll2)
(myremoveall 8 removeAll3)





;------------------------------
;       Set Functions
;------------------------------
(printf "\nSET FUNCTIONS:\n\n")


;_______________
;    Choice 1
; Set membership
(printf "1. Set membership:\n")

;Sets
(define set1 (list 2 3 1 4))
(define set2 (list 8 9 1 3))
(define emptySet (list));

;Define mymember
(define (mymember elem set1)
  (if (< 0
      (if (index-of set1 elem) 1 0))
      #t #f))

;Test cases
(mymember 2 set1)
(mymember 0 set2)
(mymember 0 emptySet)


;_______________
;    Choice 2
; Insert element into set
(printf "2. Insert element into set:\n")

; Define myinsert (in example, it adds at beggining, so I did that too, hope that is ok)
; For reference: (insert ’a ’(b c d)) => ’(a b c d)
(define (myinsert elem set1)
  (mynub (list* elem set1)))

;Test cases
(myinsert 2 set1) ; set1 is: (list 2 3 1 4), so it is not added.
(myinsert 0 set2) ; set2 is: (list 8 9 1 3), so it is added.
(myinsert 5 emptySet)


;_______________
;    Choice 3
; Set intersection
(printf "3. Set intersection:\n")

;New sets for use
(define set3 (list 2 5 1 21 4 3 6 14))
(define set4 (list 1 5 7 0 6 3 2 12))

;Define myintersection
(define finalSet (list))

;Define functions for mynub
(define (setFinalSet2 set1 elem)
  (set! finalSet (list* elem set1))
  )

(define (setFinalSet1 set1)
  (set! finalSet set1)
  )

(define (myintersection set1 set2)
  (setFinalSet1 (list))
  ;For each element, check if it is a member of both sets, and if it is add to finalSet
  (for-each (lambda (arg) (if (mymember arg set2) (setFinalSet2 finalSet arg) (printf ""))) set1)
  (myreverse finalSet)
  )

;Test cases
(myintersection set3 set1) ; set1 is: (list 2 3 1 4)
(myintersection set4 set2) ; set2 is: (list 8 9 1 3)
(myintersection set1 emptySet)



;------------------------------
;       Math Functions
;------------------------------
(printf "\nMATH FUNCTIONS:\n\n")

;Helper function for the other problems:
(define (factor? number divisor)
  (cond [(= number divisor) #f]
        [(integer? (/ number divisor)) #t]
        [else #f]))


;_______________
;    Choice 1
; Absolute Value
(printf "1. Absolute Value (Tests 2, -3, -10, 0 in that order):\n")

;Define myabs
(define (myabs num)
  (if (equal? num 0) 0
      (if (> 0 num) (- 0 num) num)
  ))

;Test cases
(myabs 2)
(myabs -3)
(myabs -10)
(myabs 0)

;_______________
;    Choice 2
;   Factorial
(printf "2. Factorial (Tests 2, 3, 6, 0 in that order):\n")

(define (myfactorial n)
  (cond [(= n 1) 1] ;base cases
        [(= n 0) 1]
        [else (* n (myfactorial (- n 1)))])) ;multiply n by factorial of (n-1)

;Test cases
(myfactorial 2)
(myfactorial 3)
(myfactorial 6)
(myfactorial 0)

;_______________
;    Choice 4
;      GCD
(printf "4. Greatest Common Divisor (Tests (8, 12), (9, 6), (10, 6), (0, 0) in that order):\n")

;Define Functions
;get the greatest common divisor of two numbers
(define (gcd n1 n2) 
  (cond [(= n1 n2) n1] ;if the numbers are equal, return the number
        [else (gcd-helper n1 n2 1 1)])) ;otherwise call helper function

(define (gcd-helper n1 n2 curFactor curNum) ;take the two numbers, current highest factor, and current number
  ;check if the curNum is a factor of both numbers, and if it is set it to curFactor
  (cond [(and (or (factor? n1 curNum) (= n1 curNum)) (or (factor? n2 curNum) (= n2 curNum))) (set! curFactor curNum)])
  (cond [(or (> curNum n1) (> curNum n2)) curFactor] ;we've checked all possible factors, return curFactor
        [else (gcd-helper n1 n2 curFactor (+ curNum 1))])) ;otherwise increment number and continue

;Test cases
(gcd 8 12)
(gcd 9 6)
(gcd 10 6)
(gcd 0 0)
;_______________
;    Choice 6
;   Nth-Fibo
(printf "6. Nth-Fibo number (Tests 6, 10, 9, 15 in that order):\n")

;Define function
(define (nth-fibo n)
  (cond [(<= n 1) n] ;base case - if n is less than or equal to 1, return n
        [else (+ (nth-fibo (- n 1)) (nth-fibo (- n 2)))])) ; otherwise, recursively add the two previous terms together

;Test cases
(nth-fibo 6)
(nth-fibo 10)
(nth-fibo 9)
(nth-fibo 15)

;_______________
;    Choice 7
;   Prime Test
(printf "7. Prime Test (Tests 2, 7, 10, 0, 1 in that order):\n")

(define (myprime number)
  (cond [(= number 1) #f] ; base case
        [else (prime-helper number (- number 1))])) ; call the helper function on number and number-1

;Checks all the numbers less than the number to see if it is divisible by any of them
(define (prime-helper number divisor)
  (cond [(= divisor 1) #t] ;if all divisors have been checked, then this is prime
        [(= (remainder number divisor) 0) #f] ;if the number is divisible by the divisor, it's not prime
        [else (prime-helper number (- divisor 1))])) ;otherwise, check for a lower divisor

;Test cases
(myprime 2)
(myprime 7)
(myprime 10)
(myprime 0)
(myprime 1)

;_______________
;    Choice 8
;   Nth prime number
(printf "8. Nth prime number (Tests 2, 7, 10, 0, 1, 6, 26 in that order):\n")

(define (nth-prime n)
  (cond [(= n 0) (printf "Not Possible\n")] ;can't have the 0th prime
        [else (nth-prime-helper n 0 1)]))
;gets the nth prime number given the current number prime and the current number
(define (nth-prime-helper n curPrime curNum) 
  (cond [(= curPrime n) (- curNum 1)] ;if we've reached the nth prime, return it
        [(myprime curNum) (nth-prime-helper n (+ curPrime 1) (+ curNum 1))] ;if current number is prime, increment curPrime
        [else (nth-prime-helper n curPrime (+ curNum 1))])) ;otherwise, call helper on the current number + 1

;Test cases
(nth-prime 2)
(nth-prime 7)
(nth-prime 10)
(nth-prime 0)
(nth-prime 1)
(nth-prime 6)
(nth-prime 26)



;------------------------------
;       Required Functions
;------------------------------
(printf "\nREQUIRED FUNCTIONS:\n\n")

;_______________
;    Choice 1
;   Check Perfect
(printf "1. Check if number is Perfect (Tests 1, 0, 2, 5, 6 in that order):\n")

;Gets whether a number is perfect - that is whether the sum of its factors is equal to the number
(define (perfect? n)
  (cond [(= n 0) #t] ;base case to account for weird possibilities
        [(= n 1) #t]
        [else (= (perfect-helper n 1 0) n)])) ;call helper function, and see if the sum of factors is equal to number

(define (perfect-helper n i sum) ;take in a number, the current divisor, and the sum
  (cond [(factor? n i) (set! sum (+ sum i))]) ;if i is a factor of n, add it to the sum 
  (cond [(< i n) (perfect-helper n (+ i 1) sum)] ;if factor is less than n, call helper on the increment of i
         [(= i n) sum])) ;if we've checked every number, return the sum

;Test cases
(perfect? 1)
(perfect? 0)
(perfect? 2)
(perfect? 5)
(perfect? 6)

;_______________
;    Choice 2
;   Abundant test
(printf "8. Check if number is Abundant (Tests 1, 0, 2, 5, 12 in that order):\n")

;Gets whether a number is abundant - that is whether the sum of its factors is greater than the number
(define (abundant? n)
  (cond [(= n 0) #f] ;base case to account for weird possibilities
        [(= n 1) #f]
        [else (> (perfect-helper n 1 0) n)])) ;call helper function, and see if the sum of factors is equal to number

;Test cases
(abundant? 1)
(abundant? 0)
(abundant? 2)
(abundant? 5)
(abundant? 12)

;_______________
;    Choice 3
;   Deficient
(printf "3. Check if number is Deficient (Tests 2, 0, 1, 5, 12, 7 in that order):\n")

;Gets whether a number is deficient - that is whether the sum of its factors is less than the number
(define (deficient? n)
  (cond [(= n 0) #f] ;base case to account for weird possibilities
        [(= n 1) #f]
        [else (< (perfect-helper n 1 0) n)])) ;call helper function, and see if the sum of factors is equal to number

;Test cases
(deficient? 2)
(deficient? 0)
(deficient? 1)
(deficient? 5)
(deficient? 12)
(deficient? 7)