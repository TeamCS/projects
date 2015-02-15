import static org.junit.Assert.*;

import org.junit.Test;

public class TestBoard {
    
    @Test
    public void testConstructor() {
        Board b1 = new Board(true);
        Board b2 = new Board(false);
        assertEquals(b1.pieceAt(0, 7), null);
        assertEquals(b1.pieceAt(1, 6), null);
        assertEquals(b1.pieceAt(2, 5), null);
        assertEquals(b1.pieceAt(3, 4), null);
        assertEquals(b2.pieceAt(4, 4), null);
        assertEquals(b2.pieceAt(4, 2).side()    , 0);
        assertEquals(b2.pieceAt(6, 6).side()    , 1);
        assertEquals(b2.pieceAt(1, 5).isBomb()  , true);
        assertEquals(b2.pieceAt(3, 1).isShield(), true);
    }
    
    @Test
    public void testPieceAt() {
        Board b = new Board(true);
        Piece p = new Piece(true, b, 1, 1, "shield");
        b.place(p, 1, 1);
        assertEquals(b.pieceAt(10, 10), null);
        assertEquals(b.pieceAt(-1, -1), null);
        assertEquals(b.pieceAt(1, 1)  , p);
    }
    
    @Test
    public void testCanSelect() {
        Board b  = new Board(false);
        Piece p1 = new Piece(false, b, 3, 3, "shield");
        b.place(p1, 3, 3);
        b.remove(6, 6);
        assertEquals(b.canSelect(0, 2), true);
        b.select(0, 2);
        assertEquals(b.canSelect(1, 3), true);
        assertEquals(b.canSelect(0, 5), false);
        assertEquals(b.canSelect(2, 2), true);
        b.select(2, 2);
        assertEquals(b.canSelect(4, 4), true);
    }
    
    @Test
    public void testSelect() {
        Board b = new Board(false);
        b.select(0, 2);
        b.select(2, 2);
        assertEquals(b.canSelect(3, 3), true);
    }
    
    @Test
    public void testPlace() {
        Board b = new Board(false);
        Piece p1 = new Piece(true , b, 5, 5, "shield");
        Piece p2 = new Piece(false, b, 5, 6, "bomb");
        b.place(p1, 5, 5);
        assertEquals(b.pieceAt(5, 5), p1);
        assertEquals(b.pieceAt(5, 6), null);
        b.place(p2, 5, 6);
        assertEquals(b.pieceAt(5, 6), p2);
        b.place(p2, 9, 9);
        assertEquals(b.pieceAt(9, 9), null);
    }
    
    @Test
    public void testRemove() {
        Board b = new Board(false);
        b.remove(9, 9);
        b.remove(4, 4);
        b.remove(1, 1);
        assertEquals(b.pieceAt(1, 1), null);
    }
    
    @Test
    public void testWinner() {
        Board b = new Board(true);
        assertEquals(b.winner(), "No one");
        Board b2 = new Board(true);
        Piece fire_pawn = new Piece(true, b2, 3, 5, "pawn");
        Piece water_pawn = new Piece(false, b2, 2, 6, "pawn");
        b2.place(fire_pawn, 3 , 5);
        b2.place(water_pawn, 2, 6);
        b2.select(3, 5);
        b2.select(1, 7);
        assertEquals(b2.winner(), "Fire");
        Board b3 = new Board(true);
        Piece fp = new Piece(true, b3, 2, 2, "pawn");
        Piece wp = new Piece(false, b3, 3, 3, "pawn");
        b3.place(fp, 2, 2);
        b3.place(wp, 3, 3);
        b3.select(3, 3);
        b3.select(1, 1);
        assertEquals(b3.winner(), "Water");
    }
    
    @Test
    public void testMultiCap(){
        Board b = new Board(true);
        b.place(new Piece(true, b, 2, 2, "pawn"), 2, 2);
        b.place(new Piece(false, b, 1, 3, "pawn"), 1, 3);
        b.place(new Piece(false, b, 1, 5, "pawn"), 1, 5);
        b.place(new Piece(false, b, 3, 5, "pawn"), 3, 5);
        b.place(new Piece(false, b, 3, 3, "pawn"), 3, 3);
        b.select(2, 2);
        b.select(0, 4);
        b.select(2, 6);
        b.select(4, 4);
        b.select(2, 2);
        assertEquals(null, b.pieceAt(1, 3));
        assertEquals(null, b.pieceAt(0, 4));
        assertEquals(null, b.pieceAt(1, 5));
        assertEquals(null, b.pieceAt(2, 6));
        assertEquals(null, b.pieceAt(3, 5));
        assertEquals(null, b.pieceAt(4, 4));
        assertEquals(null, b.pieceAt(3, 3));
    }

    public static void main(String[] args) {
        jh61b.junit.textui.runClasses(TestBoard.class);
    }
}
