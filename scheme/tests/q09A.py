test = {
  'names': [
    'q09A',
    'q9A',
    'Q9A',
    'qA9',
    'QA9',
    'A9',
    '9A',
    '9'
  ],
  'points': 1,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> repr(eval("(begin (define (f x y) (+ x y)) f)"))
        repr(LambdaProcedure(pairify(['x', 'y']), pairify(['+', 'x', 'y']), create_global_frame()))
        >>> repr(eval("(begin (define (f) (+ 2 2)) f)"))
        repr(LambdaProcedure(nil, pairify(['+', 2, 2]), create_global_frame()))
        >>> repr(eval("(begin (define (f x) (* x x)) f)"))
        repr(LambdaProcedure(pairify(['x']), pairify(['*', 'x', 'x']), create_global_frame()))
        >>> repr(eval("(begin (define (f x) 1 2) f)"))
        repr(LambdaProcedure(pairify(['x']), pairify(['begin', 1, 2]), create_global_frame()))
        >>> eval("(define (0 x) (* x x))")
        SchemeError
        """,
        'type': 'doctest'
      }
    ]
  ]
}