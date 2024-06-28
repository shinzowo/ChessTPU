#include <iostream>
#include <vector>
#include <bitset>


class ChessBoard;

class ChessPiece
{
public:
    ChessPiece(char c) : color(c) {}
    char color;
    virtual std::string getMoves(ChessBoard *board, int x, int y) = 0;
};

using board_t = std::vector<std::vector<ChessPiece *>>;
class ChessBoard
{
public:
    ChessBoard() : board(board_t(8, std::vector<ChessPiece *>(8, nullptr))), castle_flags("1111") {}
    ~ChessBoard() {}

    std::string getMoves(int x, int y)
    {
        if (board[x][y] == nullptr)
            return "";

        return board[x][y]->getMoves(this, x, y);
    }

    std::string getMoves(int x, char y)
    {
        if (board[x - 1][y - 'a'] == nullptr)
            return "";

        return board[x - 1][y - 'a']->getMoves(this, x - 1, y - 'a');
    }

    ChessPiece *getPiece(int x, int y)
    {
        if( x < 0 || x > 7 || y < 0 || y > 7) return nullptr;
        return board[x][y];
    }

    ChessPiece *getPiece(int x, char y)
    {
        return getPiece(x - 1, (int)(y - 'a'));
    }

    template <class T>
    void setPiece(int x, int y, char c)
    {
        board[x][y] = new T(c);
    }

    template <class T>
    void setPiece(int x, char y, char c)
    {
        board[x - 1][y - 'a'] = new T(c);
    }

private:
    board_t board;
    std::bitset<4> castle_flags;
};

class Pawn : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    std::string getMoves(ChessBoard *board, int x, int y) override
    {
        std::string ans = "";
        int direction = color == 'W' ? 1 : -1;
        bool first_move = x == ((7 + direction) % 7);
        if (board->getPiece(x + direction, y) == nullptr)
        {
            (ans += x + direction + '1') += y + 'a';
            if (first_move && (board->getPiece(x + 2 * direction, y) == nullptr))
            {
                (ans += x + 2 * direction + '1') += y + 'a';
            }
        }
        for (int i = -1; i < 2; i += 2)
        {
            if (board->getPiece(x + direction, y + i) != nullptr && board->getPiece(x + direction, y + i)->color != board->getPiece(x, y)->color)
            {
                (ans += x + direction + '1') += y + i + 'a';
            }
        }
        return ans;
    }
};

int main(int, char **)
{
    ChessBoard board;
    for (char i = 'a'; i <= 'h'; ++i)
    {
        board.setPiece<Pawn>(2, i, 'W');
    }

    board.setPiece<Pawn>(3, 'b', 'B');
    board.setPiece<Pawn>(3, 'a', 'B');

    std::cout << std::endl
              << board.getMoves(2, 'a') << std::endl;
}
