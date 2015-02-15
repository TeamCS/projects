info = {
  'name': 'cal/61A/fa14/proj4',
  'params': {
    'doctest': {
      'cache': r"""
      import sys
      sys.path.append('.')
      from scheme_reader import *
      from scheme import *
      import scheme_primitives
      import scheme
      
      def eval(snippet):
          buf = scheme.buffer_lines(snippet.split('\n'), show_prompt=True)
          exprs = []
          try:
              while True:
                  exprs.append(scheme.scheme_read(buf))
          except EOFError:
              pass
          env = scheme.create_global_frame()
          for expr in exprs[:-1]:
              scheme.scheme_eval(expr, env)
          return scheme.scheme_eval(exprs[-1], env)
      
      def pairify(lst):
          if not lst:
              return nil
          if type(lst) is not list:
              return lst
          if type(lst[0]) is str:
              return Pair(lst[0], pairify(lst[1:]))
          return Pair(pairify(lst[0]), pairify(lst[1:]))
      
      def make_check_scheme(file='questions.scm'):
          f = open(file, 'r')
          contents = f.read()
          def check_scheme(snippet, preamble=''):
              stuff = contents + preamble + snippet
              return str(eval(stuff))
          f.close()
          return check_scheme
      
      check_scheme = make_check_scheme()
      """,
      'setup': r"""
      
      """
    }
  },
  'src_files': [
    'scheme.py',
    'scheme_reader.py',
    'tests.scm',
    'questions.scm'
  ],
  'version': '1.0'
}