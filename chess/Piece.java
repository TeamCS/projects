
public class Piece {
    
    private int xpos, ypos;
    private Board b;
    private String type;
    private boolean team, crown, hasCap;
    
    public Piece(boolean isFire, Board b, int x, int y, String type) {
        team      = isFire;
        this.type = type;
        this.b    = b;
        xpos      = x;
        ypos      = y;
    }
    
    public boolean isFire() {
        return team; 
    }
    
    public int side() {
        if (team)   return 0;
        else        return 1;   
    }
    
    public boolean isKing() {
        return crown;
    }
    
    public boolean isBomb() {
        if (type == "bomb")     return true;
        else                    return false;
    }
    
    public boolean isShield() {
        if (type == "shield")   return true;
        else                    return false;
    }
    
    public void move(int x, int y) {
        int ox = xpos;
        int oy = ypos;
        Piece a = b.pieceAt((ox+x)/2, (oy+y)/2);
        if ((Math.abs(x-xpos) == 2) && (Math.abs(y-ypos) == 2) && a != null) {
            if (type == "bomb") {
                int[] adder = new int[]{-1, 0, 1};
                for (int a1 : adder) {
                    for (int a2 : adder) {
                        int m = x + a1;
                        int n = y + a2;
                        Piece p = b.pieceAt(m,n);
                        boolean isBombed = (p != null) && !(p.type == "shield");
                        boolean isTarget = (m == (xpos+x)/2) && (n == (ypos+y)/2);
                        if ((isTarget || isBombed)){
                            b.remove(m, n);
                        }
                    }
                }
            } else {
                hasCap = true;
                b.place(this, x, y);
                b.remove((xpos+x)/2, (ypos+y)/2);
            }   
        } else {
            b.place(this, x, y);
        }
        xpos = x;
        ypos = y;
        b.remove(ox, oy);
        boolean isfireKing = (side() == 0 && ypos == 7);
        boolean iswaterKing = (side() == 1 && ypos == 0);
        if (isfireKing || iswaterKing) {
            crown = true;
        }
    }
        
    public boolean hasCaptured() {
        return hasCap;
    }
    
    public void doneCapturing() {
        hasCap = false;
    }
}
