import static org.junit.Assert.*;

import org.junit.Test;

public class TestPiece {

    @Test
    public void testConstructor() {
        Board b = new Board(true);
        Piece p = new Piece(true, b, 1, 1, "pawn");
        assertEquals(p.isFire()     , true);
        assertEquals(p.isKing()     , false);
        assertEquals(p.hasCaptured(), false);
        assertEquals(p.isShield()   , false);
    }
    
    @Test
    public void testIsFire() {
        Board b = new Board(true);
        Piece f = new Piece(true,  b, 2, 2, "shield");
        Piece w = new Piece(false, b, 3, 3, "bomb");
        assertEquals(f.isFire(), true);
        assertEquals(w.isFire(), false);
    }
    
    @Test
    public void testSide() {
        Board b = new Board(true);
        Piece f = new Piece(true , b, 4, 4, "pawn");
        Piece w = new Piece(false, b, 5, 5, "shield");
        assertEquals(f.side(), 0);
        assertEquals(w.side(), 1);
    }
    
    @Test
    public void testIsKing() {
        Board b = new Board(true);
        Piece n1 = new Piece(true , b, 0, 7, "bomb");
        Piece n2 = new Piece(false, b, 0, 0, "pawn");
        Piece f  = new Piece(true , b, 6, 6, "shield");
        Piece w  = new Piece(false, b, 7, 1, "bomb");
        b.place(f, 6, 6);
        b.place(w, 7, 1);
        f.move(7, 7);
        w.move(6, 0);
        assertEquals(n1.isKing(), false);
        assertEquals(n2.isKing(), false);
        assertEquals(f.isKing() , true);
        assertEquals(w.isKing() , true);
    }
    
    @Test
    public void testIsBomb() {
        Board b = new Board(true);
        Piece b1 = new Piece(true , b, 1, 1, "bomb");
        Piece b2 = new Piece(false, b, 2, 2, "shield");
        assertEquals(b1.isBomb(), true);
        assertEquals(b2.isBomb(), false);
    }
    
    @Test
    public void testIsShield() {
        Board b = new Board(true);
        Piece p1 = new Piece(true , b, 3, 3, "shield");
        Piece p2 = new Piece(false, b, 4, 4, "pawn");
        assertEquals(p1.isShield(), true);
        assertEquals(p2.isShield(), false);
    }
    
    @Test
    public void testMove() {
        Board b = new Board(true);
        Piece c1 = new Piece(true , b, 0, 0, "bomb");
        Piece c2 = new Piece(false, b, 1, 1, "shield");
        Piece c3 = new Piece(false, b, 1, 2, "bomb");
        Piece c4 = new Piece(false, b, 0, 2, "bomb");
        Piece c5 = new Piece(false, b, 2, 3, "shield");
        Piece c6 = new Piece(true , b, 3, 1, "pawn");
        Piece m1 = new Piece(true , b, 4, 4, "pawn");
        Piece m2 = new Piece(false, b, 7, 7, "pawn");
        b.place(c1, 0, 0);
        b.place(c2, 1, 1);
        b.place(c3, 1, 2);
        b.place(c4, 0, 2);
        b.place(c5, 2, 3);
        b.place(c6, 3, 1);
        b.place(m1, 4, 4);
        b.place(m2, 7, 7);
        c1.move(2, 2);
        m1.move(5, 5);
        m2.move(6, 6);
        assertEquals(b.pieceAt(0, 0), null);
        assertEquals(b.pieceAt(1, 1), null);
        assertEquals(b.pieceAt(1, 2), null);
        assertEquals(b.pieceAt(0, 2), c4);
        assertEquals(b.pieceAt(2, 3), c5);
        assertEquals(b.pieceAt(3, 1), null);
        assertEquals(b.pieceAt(4, 4), null);
        assertEquals(b.pieceAt(5, 5), m1);
        assertEquals(b.pieceAt(7, 7), null);
        assertEquals(b.pieceAt(6, 6), m2);
    }
    
    @Test
    public void testHasCaptured() {
        Board b = new Board(true);
        Piece p1 = new Piece(true , b, 0, 0, "shield");
        Piece p2 = new Piece(false, b, 1, 1, "shield");
        Piece p3 = new Piece(false, b, 3, 3, "pawn");
        b.place(p1, 0, 0);
        b.place(p2, 1, 1);
        b.place(p3, 3, 3);
        p1.move(2, 2);
        assertEquals(p1.hasCaptured(), true);
        p1.move(4, 4);
        assertEquals(p1.hasCaptured(), true);
    }
    
    @Test
    public void testDoneCapturing() {
        Board b = new Board(true);
        Piece p1 = new Piece(true , b, 4, 4, "pawn");
        Piece p2 = new Piece(false, b, 5, 5, "bomb");
        b.place(p1, 4, 4);
        b.place(p2, 5, 5);
        p1.move(6, 6);
        assertEquals(p1.hasCaptured(), true);
        p1.doneCapturing();
        assertEquals(p1.hasCaptured(), false);
    }
    
    
    public static void main(String[] args) {
        jh61b.junit.textui.runClasses(TestPiece.class);
    }
}
