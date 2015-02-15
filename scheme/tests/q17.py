test = {
  'names': [
    'q17',
    'Q17',
    '17'
  ],
  'points': 2,
  'suites': [
    [
      {
        'test': r"""
        >>> eval('''
        ... (define f (mu (x) (+ x y)))
        ... (define g (lambda (x y) (f (+ x x))))
        ... (g 3 7)
        ... ''')
        13
        >>> eval('''
        ... (define g (mu () x))
        ... (define (high f x)
        ...   (f))
        ... (high g 2)
        ... ''')
        2
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'test': r"""
        >>> eval('''
        ... (define (f x) (mu () (lambda (y) (+ x y))))
        ... (define (g x) (((f (+ x 1))) (+ x 2)))
        ... (g 3)
        ... ''')
        8
        """,
        'type': 'doctest'
      }
    ]
  ]
}