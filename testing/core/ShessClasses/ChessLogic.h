#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <bitset>
#include <optional>
#include <memory>
#include <sstream>

namespace Chess
{
    class Game;
    class Board;
    class Piece;
    class Timing;
    class Move;

    enum class Color : uint8_t
    {
        None,
        Black,
        White
    };

    enum class Cell : uint8_t
    {
        // clang-format off
        a1, a2, a3, a4, a5, a6, a7, a8,
        b1, b2, b3, b4, b5, b6, b7, b8,
        c1, c2, c3, c4, c5, c6, c7, c8,
        d1, d2, d3, d4, d5, d6, d7, d8,
        e1, e2, e3, e4, e5, e6, e7, e8,
        f1, f2, f3, f4, f5, f6, f7, f8,
        g1, g2, g3, g4, g5, g6, g7, g8,
        h1, h2, h3, h4, h5, h6, h7, h8
        // clang-format on
    };

    int row(Cell cell);
    int column(Cell cell);

    Cell relativeCell(Cell cell, int r, int c);
    bool isLegalCell(Cell cell);
    Cell makeCell(int r, int c);

    enum class PieceType : uint8_t
    {
        Empty,
        King,
        Queen,
        Bishop,
        Knight,
        Rook,
        Pawn
    };

    enum class GameType : uint8_t
    {
        Classic,
        Fischer960,
        ThreeChecks
    };

    class Move
    {
    public:
        Move(Cell from, Cell to) : from(from), to(to) {}
        virtual void special(Game &game) const;

    //protected:
        Cell from;
        Cell to;
    };

    class MoveRookFirst : public Move
    {
    public:
        MoveRookFirst(Cell from, Cell to) : Move(from, to) {}
        void special(Game &game) const override;
    };

    class MoveKingFirst : public Move
    {
    public:
        MoveKingFirst(Cell from, Cell to) : Move(from, to) {}
        void special(Game &game) const override;
    };

    class MovePawnDouble : public Move
    {
    public:
        MovePawnDouble(Cell from, Cell to) : Move(from, to) {}
        void special(Game &game) const override;
    };

    class MoveEnPassant : public Move
    {
    public:
        MoveEnPassant(Cell from, Cell to) : Move(from, to) {}
        void special(Game &game) const override;
    };

    class Piece
    {
    public:
        explicit Piece(Color color) : color(color) {}
        virtual std::vector<std::unique_ptr<Move>> getRelativeMoves(const Game &game, Cell cell) const = 0;

        // protected:
        Color color;
    };

    class Pawn : public Piece
    {
    public:
        explicit Pawn(Color color) : Piece(color) {}
        std::vector<std::unique_ptr<Move>> getRelativeMoves(const Game &game, Cell cell) const override;
    };

    class Knight : public Piece
    {
    public:
        explicit Knight(Color color) : Piece(color) {}
        std::vector<std::unique_ptr<Move>> getRelativeMoves(const Game &game, Cell cell) const override;
    };

    class Bishop : public Piece
    {
    public:
        explicit Bishop(Color color) : Piece(color) {}
        std::vector<std::unique_ptr<Move>> getRelativeMoves(const Game &game, Cell cell) const override;
    };

    class Rook : public Piece
    {
    public:
        explicit Rook(Color color, bool isFirstMove = false)
            : Piece(color), isFirstMove(isFirstMove) {}

        bool isFirstMove;
        std::vector<std::unique_ptr<Move>> getRelativeMoves(const Game &game, Cell cell) const override;
        Move *chooseMoveType(Cell from, Cell to) const;
    };

    class Queen : public Piece
    {
    public:
        explicit Queen(Color color) : Piece(color) {}
        std::vector<std::unique_ptr<Move>> getRelativeMoves(const Game &game, Cell cell) const override;
    };

    class King : public Piece
    {
    public:
        explicit King(Color color) : Piece(color), isFirstMove(true) {}
        bool isFirstMove;
        std::vector<std::unique_ptr<Move>> getRelativeMoves(const Game &game, Cell cell) const override;
        Move *chooseMoveType(Cell from, Cell to) const;
    };

    enum class CastlingRights : uint8_t
    {
        // clang-format off
        None       = 0,

        BlackKing  = 1,
        BlackQueen = 2,
        BlackAll   = 3,

        WhiteKing  = 4,
        WhiteQueen = 8,
        WhiteAll   = 12,

        All        = 15
        // clang-format on
    };

    inline CastlingRights operator|(CastlingRights left, CastlingRights right);
    inline CastlingRights &operator|=(CastlingRights &left, CastlingRights right);
    inline CastlingRights operator&(CastlingRights left, CastlingRights right);
    inline CastlingRights &operator&=(CastlingRights &left, CastlingRights right);
    inline CastlingRights operator^(CastlingRights left, CastlingRights right);
    inline CastlingRights &operator^=(CastlingRights &left, CastlingRights right);

    class Board
    {
    public:
        static Board StartingPosition() { return Board(); }
        Board(const std::string &fen);
        Board() : Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {}
        Board(const Board &board);
        // Board copy() const;
        const Piece *const &operator[](Cell cell) const;
        Piece *&operator[](Cell cell);

    private:
        Piece *board[8][8];
    };

    class Game
    {
    public:
        // Game(Color _active_player, const Board &_board = Board::StartingPosition(), CastlingRights _castling_flags = CastlingRights::All, std::optional<Cell> _ep = std::nullopt);
        Game(const std::string &fen);
        bool checkMove(const Move &move);
        bool isKingInCheck(Color kingColor) const;
        // private:
        Board board;
        Board next_board;
        Color active_player;
        CastlingRights castling_flags;
        Cell en_passant;
    };

}

#endif // CHESSLOGIC_H