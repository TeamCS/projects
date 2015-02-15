test = {
  'names': [
    'q10',
    'Q10',
    '10'
  ],
  'params': {
    'doctest': {
      'setup': r"""
      global_frame = create_global_frame()
      """
    }
  },
  'points': 2,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> frame = global_frame.make_call_frame(pairify(["a", "b", "c"]), pairify([1, 2, 3]))
        >>> frame.parent
        global_frame
        >>> frame.lookup('a')
        1
        >>> frame.lookup('b')
        2
        >>> frame.lookup('c')
        3
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> frame = global_frame.make_call_frame(nil, nil)
        >>> frame.parent
        global_frame
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> first = Frame(global_frame)
        >>> second = first.make_call_frame(nil, nil)
        >>> second.parent
        first
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'never_lock': True,
        'test': r"""
        >>> global_frame.make_call_frame(pairify(["a"]), pairify([1, 2, 3]))
        SchemeError
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> global_frame.make_call_frame(pairify(["a", "b", "c"]), pairify([1]))
        SchemeError
        """,
        'type': 'doctest'
      }
    ]
  ]
}