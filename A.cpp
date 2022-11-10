#include <iostream>

class Cell final {
public:
    char v; 					                         // Вертикаль, от 'A' до 'H'
    unsigned short int h;		                         // Горизонталь, от '1' до '8'
    Cell(): Cell('A',1) {}			                     // Конструктор клетки по умолчанию
    Cell(char v, unsigned short int h): v(v), h(h) {}	 // Конструктор заданной клетки поля с параметрами
};

struct Delta {
    int dx, dy;
};

class Piece {
protected:
    Cell pos;

    Delta distance(Cell a) const {
        int dx, dy;
        if (pos.h >= a.h)
            dx = pos.h - a.h;
        else
            dx = a.h - pos.h;

        if (pos.v >= a.v)
            dy = pos.v - a.v;
        else
            dy = a.v - pos.v;

        return Delta{dx, dy};
    }

public:
    Piece(Cell pos): pos(pos) {  };
    
    virtual ~Piece() {  };

    virtual bool available(Cell c) const = 0;
};

class King final : public Piece {
public:
    King(Cell pos): Piece(pos) {  };

    bool available(Cell c) const override {
        Delta delta = distance(c);
        auto delta_sum = delta.dx + delta.dy;
        return (1 <= delta_sum && delta_sum <= 2);
    }
};

class Bishop final : public Piece {
public:
    Bishop(Cell pos): Piece(pos) {  };

    bool available(Cell c) const override {
        Delta delta = distance(c);
        return (delta.dx == delta.dy && delta.dx != 0);
    }
};

class Rook final : public Piece {
public:
    Rook(Cell pos): Piece(pos) {  };

    bool available(Cell c) const override {
        Delta delta = distance(c);
        return (delta.dx == 0 ^ delta.dy == 0);
    }
};

class Queen final : public Piece {
public:
    Queen(Cell pos): Piece(pos) {  };

    bool available(Cell c) const override {
        Delta delta = distance(c);
        return (delta.dx == 0 ^ delta.dy == 0) || (delta.dx == delta.dy && delta.dx != 0);
    }
};

void are_available(Cell c, const Piece **pieces, bool *availability, std::size_t pieces_count) {
    for (std::size_t piece_idx = 0; piece_idx != pieces_count; ++piece_idx)
        availability[piece_idx] = pieces[piece_idx]->available(c);
}

int main() {
    const std::size_t size = 4;
    const Piece * pieces[size];
    bool availability[size];

    pieces[0] = new King(Cell('A',1));
    pieces[1] = new Queen(Cell('B',2));
    pieces[2] = new Rook(Cell('C',3));
    pieces[3] = new Bishop(Cell('D',4));

    are_available(Cell('A', 1), pieces, availability, size);
    for(auto ans : availability)
        std::cout << ans << ' ';
    std::cout << std::endl;

    for (auto p : pieces)
        delete p;
    return 0;
}
