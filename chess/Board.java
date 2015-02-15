/*
pulled down and modified.

*/
public class Board {
    
    private Piece[][] content = new Piece[8][8];
    private Piece selected;
    private int sx, sy;
    private boolean moved;
    private boolean player = true;
    private int fireNum = 0;
    private int waterNum = 0;
    
    public static void main(String args[]) {
        Board b = new Board(false);
        StdDrawPlus.setCanvasSize();
        StdDrawPlus.setXscale(0, 8);
        StdDrawPlus.setYscale(0, 8);
        Board.DrawBoard();
        Board.DrawPieces(b);
        while (true) {
            if (StdDrawPlus.mousePressed()) {
                double mx = StdDrawPlus.mouseX();
                double my = StdDrawPlus.mouseY();
                int x = (int) mx;
                int y = (int) my;
                if (b.canSelect(x, y)) {
                    b.select(x, y);
                    b.display(x, y);
                }
            }
            if (StdDrawPlus.isSpacePressed()) {
                if (b.canEndTurn()) {
                    b.endTurn();
                    Board.DrawBoard();
                    Board.DrawPieces(b);
                    StdDrawPlus.show(100);
                }
            }
            if (b.fireNum == 0 || b.waterNum == 0) {
                System.out.println(b.winner());
                return;
            }
        }
    }
    
    private void display(int x, int y) {
        StdDrawPlus.show(10);
        Board.DrawBoard();
        StdDrawPlus.setPenColor(StdDrawPlus.CYAN);
        StdDrawPlus.filledSquare(x + .5, y + .5, 0.5);
        Board.DrawPieces(this);
        StdDrawPlus.show(10);
    }
    
    public Board(boolean shouldBeEmpty) {
        if (!shouldBeEmpty) {
            int [] row    = new int[]{0, 1, 2, 5, 6, 7};
            int [] column = new int[]{0, 2, 4, 6};
            for (int r : row) {
                for (int c : column) {
                    boolean s;
                    String  t = "";
                    if (r > 4)  s = false;
                    else        s = true;
                    if ((r == 0) || (r == 7))   t = "pawn";
                    if ((r == 1) || (r == 6))   t = "shield";
                    if ((r == 2) || (r == 5))   t = "bomb";
                    if (r%2 == 0)   place(new Piece(s, this, c  , r, t), c  , r);
                    else            place(new Piece(s, this, c+1, r, t), c+1, r);
                }
            }
        }
    }
    
    public Piece pieceAt(int x, int y) {
        if (!inrange(x, y)) return null;
        else                return content[x][y];
    }
    
    public boolean canSelect(int x, int y) {
        Piece p = pieceAt(x, y);
        boolean isPnull = (p == null);
        boolean isSnull = (selected == null);
        boolean isMoved = (moved == true);
        if (!isPnull) {
            boolean b1 = !isMoved;
            boolean b2 = (p.isFire() == player);
            return (b1 && b2 && inrange(x, y));
        } else if (isPnull && !isSnull) {
            boolean isvalidMove    = validMove(sx, sy, x, y);
            boolean isvalidCapture = validCapture(sx, sy, x, y);
            boolean hasCaptured    = selected.hasCaptured();
            boolean b1 = (!isMoved && isvalidMove);
            boolean b2 = ((!isMoved || hasCaptured) && isvalidCapture);
            return (b1 || b2) && inrange(x, y);
        }
        return false;
    }
    
    private boolean validMove(int xi, int yi, int xf, int yf) {
        boolean isStartKing  = pieceAt(xi, yi).isKing();
        boolean isEndnull    = (pieceAt(xf, yf) == null);
        boolean hasXmove     = ((xf == xi+1) || (xf == xi-1));
        boolean hasYmoveup   = (yf == yi+1);
        boolean hasYmovedown = (yf == yi-1);
        if ((isEndnull && hasXmove && inrange(xf, yf))) {
            if (isStartKing)    return (hasYmoveup || hasYmovedown);
            if (player)         return (hasYmoveup);
            if (!player)        return (hasYmovedown);     
        }
        return (isEndnull && validCapture(xi, yi, xf, yf));
    }
    
    private boolean validCapture(int xi, int yi, int xf, int yf) {
        Piece mid = pieceAt((xi+xf)/2, (yi+yf)/2);
        boolean isStartKing     = pieceAt(xi, yi).isKing();
        boolean hasXmovetwo     = ((xf == xi+2) || (xf == xi-2));
        boolean hasYmoveuptwo   = (yf == yi+2);
        boolean hasYmovedowntwo = (yf == yi-2);
        boolean isOpp = false;
        if (mid != null)   isOpp = (mid.side() != pieceAt(xi, yi).side());
        if (hasXmovetwo && inrange(xf, yf) && isOpp) {
            if (isStartKing)                         return (hasYmoveuptwo || hasYmovedowntwo);
            if (pieceAt(xi, yi).side() == 0)         return (hasYmoveuptwo);
            if (pieceAt(xi, yi).side() == 1)         return (hasYmovedowntwo);
        }
        return false;
    }
    
    public void select(int x, int y) {
        boolean m1 = (Math.abs(sx-x) == 2 && Math.abs(sy-y) == 2);
        boolean m2 = (Math.abs(sx-x) == 1 && Math.abs(sy-y) == 1);
        if (selected != null && (m1 || m2)) {
            if (Math.abs(sx-x) == 2 && !selected.isBomb()) {
                selected.move(x, y);
                moved = true;
                sx = x;
                sy = y;
                return;
            }
            selected.move(x, y);
            moved = true;
            selected = null;
        } else {
            selected = pieceAt(x, y);
            if (selected != null) {
                sx = x;
                sy = y;
            }
        }
    }
    
    public void place(Piece p, int x, int y) {
        if (inrange(x, y) && (p != null)) {
            content[x][y] = p;
            if (p.side() == 0)  fireNum++;
            else                waterNum++;
            }
        }
    
    public Piece remove(int x, int y) {
        if (!inrange(x, y)) {
            System.out.println("input out of bounds.");
            return null;
        } else if (pieceAt(x, y) == null) {
            System.out.println("no piece at this location.");
            return null;
        } else {
            Piece removed = pieceAt(x, y);
            content[x][y] = null;
            if (removed.side() == 0) fireNum--;
            else                     waterNum--;
            return removed;
        }
    }
    
    public boolean canEndTurn() {
        return moved;
    }
    
    public void endTurn() {
        if (canEndTurn()) {
            if (selected != null)   selected.doneCapturing();
            selected = null;
            moved = false;
            player = !player;
        }
    }
    
    public String winner() {
        if (waterNum == 0 && fireNum == 0)  return "No one";
        if (fireNum  == 0)                  return "Water";
        if (waterNum == 0)                  return "Fire";
        else                                return null;
    }
    
    private static void DrawBoard() {
        for (double i = 0; i <= 7; i++) {
            for (double j = 0; j <= 7; j++) {
                if ((i + j) % 2 == 0) StdDrawPlus.setPenColor(StdDrawPlus.LIGHT_GRAY);
                else                  StdDrawPlus.setPenColor(StdDrawPlus.BOOK_BLUE);
                StdDrawPlus.filledSquare(i + .5, j + .5, .5);
            }
        }
    }
    
    private static void DrawPieces(Board b) {
        for (int i = 0; i <= 7; i++) {
            for (int j = 0; j <= 7; j++) {
                Piece p = b.content[i][j];
                if (p != null) {
                    int s = p.side();
                    String type = "pawn";
                    String crown = "";
                    String team;
                    if (p.isBomb())     type = "bomb";
                    if (p.isShield())   type = "shield";
                    if (p.isKing())     crown = "-crowned";
                    if (s == 0)         team = "fire";
                    else                team = "water";
                    String filename = String.format("img/%s-%s%s.png", type, team, crown);
                    StdDrawPlus.picture(i + .5, j + .5, filename, 1, 1);
                }
            }
        }
    }
    
    private boolean inrange(int x, int y) {
        if (x > 7 || x < 0 || y > 7 || y < 0)   return false;
        else                                    return true;
    }
}
