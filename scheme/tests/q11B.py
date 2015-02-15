test = {
  'names': [
    'q11B',
    'Q11B',
    'qB11',
    'QB11',
    'B11',
    '11B',
    '11'
  ],
  'points': 1,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> repr(eval("(lambda (x y z) x)"))
        repr(LambdaProcedure(pairify(['x', 'y', 'z']), 'x', create_global_frame()))
        >>> eval("(lambda (0 y z) x)")
        SchemeError
        >>> eval("(lambda (x y nil) x)")
        SchemeError
        >>> eval("(lambda (x y (and z)) x)")
        SchemeError
        >>> eval("(lambda (x #t z) x)")
        SchemeError
        >>> eval("(lambda (h e l l o) 'world)")
        SchemeError
        >>> eval("(lambda (c s 6 1 a) 'yay)")
        SchemeError
        """,
        'type': 'doctest'
      }
    ]
  ]
}