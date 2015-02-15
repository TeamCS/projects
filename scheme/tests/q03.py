test = {
  'names': [
    'q03',
    'q3',
    'Q3',
    '3'
  ],
  'points': 2,
  'suites': [
    [
      {
        'test': r"""
        >>> env = create_global_frame()
        >>> twos = Pair(2, Pair(2, nil))
        >>> plus = PrimitiveProcedure(scheme_add) # + procedure
        >>> scheme_apply(plus, twos, env)
        4
        # choice: 4
        # choice: SchemeError
        """,
        'type': 'doctest'
      },
      {
        'test': r"""
        >>> env = create_global_frame()
        >>> twos = Pair(2, Pair(2, nil))
        >>> oddp = PrimitiveProcedure(scheme_oddp) # odd? procedure
        >>> scheme_apply(oddp, twos, env)
        SchemeError
        # choice: True
        # choice: False
        # choice: SchemeError
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> env = create_global_frame()
        >>> two = Pair(2, nil)
        >>> eval = PrimitiveProcedure(scheme_eval, True) # eval procedure
        >>> scheme_apply(eval, two, env) # be sure to check use_env
        2
        """,
        'type': 'doctest'
      }
    ]
  ]
}