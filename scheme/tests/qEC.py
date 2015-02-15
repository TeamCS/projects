test = {
  'names': [
    'qEC',
    'q22',
    'Q22',
    '22',
    'EC'
  ],
  'points': 4,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> eval('''
        ... (define (sum n total)
        ...   (if (zero? n) total
        ...   (sum (- n 1) (+ n total))))
        ... (sum 1001 0)
        ... ''')
        501501
        >>> eval('''
        ... (define (sum n total)
        ...   (if (zero? n) total
        ...   (if #f 42 (sum (- n 1) (+ n total)))))
        ... (sum 1001 0)
        ... ''')
        501501
        >>> eval('''
        ... (define (sum n total)
        ...   (cond ((zero? n) total)
        ...     ((zero? 0) (sum (- n 1) (+ n total)))
        ...     (else 42)))
        ... (sum 1001 0)
        ... ''')
        501501
        >>> eval('''
        ... (define (sum n total)
        ...   (if (zero? n) total
        ...   (add n (+ n total))))
        ... (define add (lambda (x+1 y) (sum (- x+1 1) y)))
        ... (sum 1001 0)
        ... ''')
        501501
        >>> eval('''
        ... (define (sum n total)
        ...   (if (zero? n) total
        ...   (let ((n-1 (- n 1)))
        ...     (sum n-1 (+ n total)))))
        ... (sum 1001 0)
        ... ''')
        501501
        """,
        'type': 'doctest'
      }
    ]
  ]
}