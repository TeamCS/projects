test = {
  'names': [
    'q08',
    'q8',
    'Q8',
    '8'
  ],
  'points': 2,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> repr(eval("(lambda (x y) (+ x y))"))
        repr(LambdaProcedure(pairify(['x', 'y']), pairify(['+', 'x', 'y']), create_global_frame()))
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'never_lock': True,
        'test': r"""
        >>> repr(eval("(lambda (x) (+ x) (+ x x))"))
        repr(LambdaProcedure(pairify(['x']), pairify(['begin', ['+', 'x'], ['+', 'x', 'x']]), create_global_frame()))
        >>> repr(eval("(lambda () 2)"))
        repr(LambdaProcedure(nil, 2, create_global_frame()))
        """,
        'type': 'doctest'
      }
    ]
  ]
}