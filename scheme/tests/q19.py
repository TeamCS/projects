test = {
  'names': [
    'q19',
    'Q19',
    '19'
  ],
  'params': {
    'doctest': {
      'setup': r"""
      def check_scheme_Q19(s):
          return check_scheme(s, '''
            ; True if ss is a list of lists
            (define (sol-lol ss)
              (cond ((null? ss) #t)
                ((not (list? ss)) #f)
                ((and (list? (car ss))
                    (sol-lol (cdr ss))) #t)
                (else #f)))
      
            ; True if ss contains s
            (define (sol-contains s ss)
              (and (not (null? ss))
                 (or (and (number? s) (= s (car ss)))
                   (and (list? s) (sol-contains-all s (car ss)))
                   (sol-contains s (cdr ss)))))
      
            ; True if ss2 contains all elements of ss1
            (define (sol-contains-all ss1 ss2)
              (or (null? ss1)
                (and (sol-contains (car ss1) ss2)
                   (sol-contains-all (cdr ss1) ss2))))
      
            ; True if ss1 and ss2 are the same list of lists
            (define (sol-same-lols ss1 ss2)
              (and (sol-lol ss1)
                 (sol-lol ss2)
                 (sol-contains-all ss1 ss2)
                 (sol-contains-all ss2 ss1)))
            ''')
      """
    }
  },
  'points': 1,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> check_scheme_Q19('''
        ... (sol-same-lols (list-partitions 5 2 4) '((4 1) (3 2)))
        ... ''')
        'True'
        >>> check_scheme_Q19('''
        ... (sol-same-lols (list-partitions 7 3 5)
        ... '((5 1 1) (4 2 1) (3 3 1) (3 2 2) (5 2) (4 3)))
        ... ''')
        'True'
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> check_scheme_Q19('''
        ... (sol-same-lols (list-partitions 7 2 4) '((4 3)))
        ... ''')
        'True'
        >>> check_scheme_Q19('''
        ... (sol-same-lols (list-partitions 7 7 1) '((1 1 1 1 1 1 1)))
        ... ''')
        'True'
        """,
        'type': 'doctest'
      }
    ]
  ]
}