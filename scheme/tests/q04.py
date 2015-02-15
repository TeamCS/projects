test = {
  'names': [
    'q04',
    'q4',
    'Q4',
    '4'
  ],
  'points': 2,
  'suites': [
    [
      {
        'test': r"""
        >>> global_frame = create_global_frame()
        >>> global_frame.define("x", 3)
        >>> global_frame.parent   # parent of the global frame
        None
        >>> global_frame.lookup("x")
        3
        >>> global_frame.lookup("foo")
        SchemeError
        # choice: None
        # choice: SchemeError
        # choice: 3
        """,
        'type': 'doctest'
      },
      {
        'test': r"""
        >>> first_frame = create_global_frame()
        >>> first_frame.define("x", 3)
        >>> second_frame = Frame(first_frame)
        >>> second_frame.parent
        first_frame
        # choice: None
        # choice: first_frame
        # choice: second_frame
        >>> second_frame.lookup("x")
        3
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'never_lock': True,
        'test': r"""
        >>> eval("(+ 2 3)")
        5
        >>> eval("(+)")
        0
        >>> eval("(* (+ 3 2) (+ 1 7))")
        40
        >>> eval("(odd? 13)")
        True
        >>> eval("(car (list 1 2 3 4))")
        1
        >>> eval("hello")
        SchemeError
        >>> eval("(car car)")
        SchemeError
        >>> eval("(odd? 1 2 3)")
        SchemeError
        """,
        'type': 'doctest'
      }
    ]
  ]
}