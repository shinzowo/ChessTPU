#include "ChessLogic.h"

std::vector<std::unique_ptr<Chess::Move>> Chess::Pawn::getRelativeMoves(const Game &game, Cell cell) const
{
    std::vector<std::unique_ptr<Chess::Move>> result;
    int direction = this->color == Color::White ? 1 : -1;
    int start_row = this->color == Color::White ? 1 : 6;
    const Piece *next_piece = game.board[relativeCell(cell, direction, 0)];
    if (next_piece == nullptr)
    {
        result.push_back(std::make_unique<Move>(Move(cell, relativeCell(cell, direction, 0))));
        next_piece = game.board[relativeCell(cell, 2 * direction, 0)];
        if (row(cell) == start_row && next_piece == nullptr)
        {
            result.push_back(std::make_unique<MovePawnDouble>(MovePawnDouble(cell, relativeCell(cell, 2 * direction, 0))));
        }
    }
    for (int i = -1; i <= 1; i += 2)
    {
        Cell next_cell = relativeCell(cell, direction, i);
        if (!isLegalCell(next_cell))
            continue;
        next_piece = game.board[next_cell];
        if (next_piece != nullptr && next_piece->color != this->color)
        {
            result.push_back(std::make_unique<Move>(Move(cell, next_cell)));
        }
        else if (game.en_passant == next_cell && ((row(next_cell) == 5 && this->color == Color::White) || (row(next_cell) == 2 && this->color == Color::Black)))
        {
            result.push_back(std::make_unique<MoveEnPassant>(MoveEnPassant(cell, next_cell)));
        }
    }

    return result;
}

Chess::Board::Board(const std::string &fen)
{
    std::vector<std::string> fields;
    std::istringstream stream(fen);
    std::string field;

    while (std::getline(stream, field, ' '))
        fields.push_back(field);

    std::string piece_placement = fields[0];

    int row = 7;
    int col = 0;

    for (char ch : piece_placement)
    {
        if (ch == '/')
        {
            row--;
            col = 0;
        }
        else if (std::isdigit(ch))
        {
            col += ch - '0';
        }
        else
        {
            Color piece_color = std::isupper(ch) ? Color::White : Color::Black;
            Piece *piece = nullptr;

            switch (std::tolower(ch))
            {
            case 'p':
                piece = new Pawn(piece_color);
                break;
            case 'r':
                piece = new Rook(piece_color);
                break;
            case 'n':
                piece = new Knight(piece_color);
                break;
            case 'b':
                piece = new Bishop(piece_color);
                break;
            case 'q':
                piece = new Queen(piece_color);
                break;
            case 'k':
                piece = new King(piece_color);
                break;
            }

            if (piece)
            {
                board[row][col] = piece;
                col++;
            }
        }
    }
}

Chess::Board::Board(const Board &board)
{
    for (int i = 0; i <= 7; ++i)
        for (int j = 0; j <= 7; ++j)
        {
            this->board[i][j] = board.board[i][j];
        }
}

const Chess::Piece *const &Chess::Board::operator[](Cell cell) const
{
    return board[row(cell)][column(cell)];
}

Chess::Piece *&Chess::Board::operator[](Cell cell)
{
    return board[row(cell)][column(cell)];
}

std::vector<std::unique_ptr<Chess::Move>> Chess::Rook::getRelativeMoves(const Game &game, Cell cell) const
{
    std::vector<std::unique_ptr<Move>> result;

    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (auto &direction : directions)
    {
        Cell next_cell = relativeCell(cell, direction.first, direction.second);
        while (isLegalCell(next_cell) && (game.board[next_cell] == nullptr || game.board[next_cell]->color != this->color))
        {
            result.push_back(std::unique_ptr<Move>(chooseMoveType(cell, next_cell)));
            if (game.board[next_cell]->color != this->color)
                break;
            next_cell = relativeCell(next_cell, direction.first, direction.second);
        }
    }

    return result;
}

Chess::Move *Chess::Rook::chooseMoveType(Cell from, Cell to) const
{
    return isFirstMove ? new MoveRookFirst(from, to) : new Move(from, to);
}

std::vector<std::unique_ptr<Chess::Move>> Chess::Bishop::getRelativeMoves(const Game &game, Cell cell) const
{
    std::vector<std::unique_ptr<Move>> result;

    std::vector<std::pair<int, int>> directions = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (auto &direction : directions)
    {
        Cell next_cell = relativeCell(cell, direction.first, direction.second);
        while (isLegalCell(next_cell) && (game.board[next_cell] == nullptr || game.board[next_cell]->color != this->color))
        {
            result.push_back(std::make_unique<Move>(Move(cell, next_cell)));
            if (game.board[next_cell]->color != this->color)
                break;
            next_cell = relativeCell(next_cell, direction.first, direction.second);
        }
    }

    return result;
}

std::vector<std::unique_ptr<Chess::Move>> Chess::Queen::getRelativeMoves(const Game &game, Cell cell) const
{
    std::vector<std::unique_ptr<Move>> result;

    std::vector<std::pair<int, int>> directions = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (auto &direction : directions)
    {
        Cell next_cell = relativeCell(cell, direction.first, direction.second);
        while (isLegalCell(next_cell) && (game.board[next_cell] == nullptr || game.board[next_cell]->color != this->color))
        {
            result.push_back(std::make_unique<Move>(Move(cell, next_cell)));
            if (game.board[next_cell]->color != this->color)
                break;
            next_cell = relativeCell(next_cell, direction.first, direction.second);
        }
    }

    return result;
}

std::vector<std::unique_ptr<Chess::Move>> Chess::Knight::getRelativeMoves(const Game &game, Cell cell) const
{
    std::vector<std::unique_ptr<Move>> result;

    std::vector<std::pair<int, int>> directions = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {-2, 1}, {-2, -1}, {2, 1}, {2, -1}};

    for (auto &direction : directions)
    {
        Cell next_cell = relativeCell(cell, direction.first, direction.second);
        if (isLegalCell(next_cell) && (game.board[next_cell] == nullptr || game.board[next_cell]->color != this->color))
        {
            result.push_back(std::make_unique<Move>(Move(cell, next_cell)));
        }
    }

    return result;
}

std::vector<std::unique_ptr<Chess::Move>> Chess::King::getRelativeMoves(const Game &game, Cell cell) const
{
    std::vector<std::unique_ptr<Move>> result;

    std::vector<std::pair<int, int>> directions = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (auto &direction : directions)
    {
        Cell next_cell = relativeCell(cell, direction.first, direction.second);
        if (isLegalCell(next_cell) && (game.board[next_cell] == nullptr || game.board[next_cell]->color != this->color))
        {
            result.push_back(std::unique_ptr<Move>(chooseMoveType(cell, next_cell)));
        }
    }
    if (this->isFirstMove && !game.isKingInCheck(this->color))
    {
        // Check for kingside castling
        if ((this->color == Color::White && ((game.castling_flags & CastlingRights::WhiteKing) == CastlingRights::WhiteKing)) ||
            (this->color == Color::Black && ((game.castling_flags & CastlingRights::BlackKing) == CastlingRights::BlackKing)))
        {
            Cell rook_cell = this->color == Color::White ? Cell::h1 : Cell::h8;
            Cell path1 = relativeCell(cell, 0, 1);
            Cell path2 = relativeCell(cell, 0, 2);
            if (game.board[path1] == nullptr && game.board[path2] == nullptr && !game.isCellAttacked(path1, this->color) && !game.isCellAttacked(path2, this->color))
            {
                result.push_back(std::make_unique<MoveCastling>(MoveCastling(cell, path2, CastlingType::KingSide)));
            }
        }

        // Check for queenside castling
        if ((this->color == Color::White && ((game.castling_flags & CastlingRights::WhiteQueen) == CastlingRights::WhiteQueen)) ||
            (this->color == Color::Black && ((game.castling_flags & CastlingRights::BlackQueen) == CastlingRights::BlackQueen)))
        {
            Cell rook_cell = this->color == Color::White ? Cell::a1 : Cell::a8;
            Cell path1 = relativeCell(cell, 0, -1);
            Cell path2 = relativeCell(cell, 0, -2);
            Cell path3 = relativeCell(cell, 0, -3);
            if (game.board[path1] == nullptr && game.board[path2] == nullptr && game.board[path3] == nullptr && !game.isCellAttacked(path1, this->color) && !game.isCellAttacked(path2, this->color))
            {
                result.push_back(std::make_unique<MoveCastling>(MoveCastling(cell, path2, CastlingType::QueenSide)));
            }
        }
    }

    return result;
}

Chess::Move *Chess::King::chooseMoveType(Cell from, Cell to) const
{
    return isFirstMove ? new MoveKingFirst(from, to) : new Move(from, to);
}

void Chess::Move::special(Game &game) const {}

void Chess::MovePawnDouble::special(Game &game) const
{
    game.en_passant = makeCell((row(from) + row(to)) / 2, column(from));
}

void Chess::MoveEnPassant::special(Game &game) const
{
    game.board[makeCell(row(from), column(to))] = nullptr;
}

int Chess::row(Cell cell)
{
    return static_cast<int>(cell) % 8;
}

int Chess::column(Cell cell)
{
    return static_cast<int>(cell) / 8;
}

Chess::Cell Chess::relativeCell(Cell cell, int r, int c)
{
    return makeCell(row(cell) + r, column(cell) + c);
}

bool Chess::isLegalCell(Cell cell)
{
    return static_cast<uint8_t>(cell) < 64;
}

Chess::Cell Chess::makeCell(int r, int c)
{
    if (c < 0 || c > 7 || r < 0 || r > 7)
    {
        throw std::out_of_range("Invalid cell coordinates");
    }
    return static_cast<Cell>(c * 8 + r);
}

inline Chess::CastlingRights Chess::operator|(CastlingRights left, CastlingRights right)
{
    return static_cast<CastlingRights>(
        static_cast<std::underlying_type_t<CastlingRights>>(left) |
        static_cast<std::underlying_type_t<CastlingRights>>(right));
}

inline Chess::CastlingRights &Chess::operator|=(CastlingRights &left, CastlingRights right)
{
    left = left | right;
    return left;
}

inline Chess::CastlingRights Chess::operator&(CastlingRights left, CastlingRights right)
{
    return static_cast<CastlingRights>(
        static_cast<std::underlying_type_t<CastlingRights>>(left) &
        static_cast<std::underlying_type_t<CastlingRights>>(right));
}

inline Chess::CastlingRights &Chess::operator&=(CastlingRights &left, CastlingRights right)
{
    left = left & right;
    return left;
}

inline Chess::CastlingRights Chess::operator^(CastlingRights left, CastlingRights right)
{
    return static_cast<CastlingRights>(
        static_cast<std::underlying_type_t<CastlingRights>>(left) ^
        static_cast<std::underlying_type_t<CastlingRights>>(right));
}

inline Chess::CastlingRights &Chess::operator^=(CastlingRights &left, CastlingRights right)
{
    left = left ^ right;
    return left;
}

// Chess::Game::Game(Color _active_player, const Board &_board, CastlingRights _castling_flags, std::optional<Cell> _ep) : active_player(_active_player), board(_board.copy()), next_board(board), castling_flags(_castling_flags), en_passant(_ep.value_or(static_cast<Cell>(-1)))

Chess::Game::Game(const std::string &fen)
{

    std::vector<std::string> fields;
    std::istringstream stream(fen);
    std::string field;

    while (std::getline(stream, field, ' '))
        fields.push_back(field);

    this->board = Board(fen);

    castling_flags = CastlingRights::None;
    for (char ch : fields[2])
    {
        switch (ch)
        {
        case 'K':
            castling_flags |= CastlingRights::WhiteKing;
            break;
        case 'Q':
            castling_flags |= CastlingRights::WhiteQueen;
            break;
        case 'k':
            castling_flags |= CastlingRights::BlackKing;
            break;
        case 'q':
            castling_flags |= CastlingRights::BlackQueen;
            break;
        default:
            break;
        }
    }

    if (fields[3] == "-")
    {
        en_passant = static_cast<Cell>(-1);
    }
    else
    {
        int file = fields[3][0] - 'a';
        int rank = fields[3][1] - '1';
        en_passant = makeCell(rank, file);
    }
}

bool Chess::Game::checkMove(const Move &move)
{

    next_board = board;

    next_board[move.to] = next_board[move.from];
    next_board[move.from] = nullptr;

    move.special(*this);

    return !isKingInCheck(active_player);
}

std::vector<std::unique_ptr<Chess::Move>> Chess::Game::getMoves()
{
    std::vector<std::unique_ptr<Chess::Move>> result;
    for (int i = 0; i < 64; ++i)
    {
        Cell cell = static_cast<Cell>(i);
        if (board[cell])
        {
            std::vector<std::unique_ptr<Chess::Move>> moves = board[cell]->getRelativeMoves(*this, cell);
            for (int j = 0; j < moves.size(); j++)
            {
                result.push_back(std::move(moves[i]));
            }
        }
    }

    return result;
}

void Chess::Game::performMove(const Move &move)
{
    board[move.to] = board[move.from];
    board[move.from] = nullptr;

    move.special(*this);
    active_player = active_player == Color::White ? Color::Black : Color::White;
}

void Chess::MoveRookFirst::special(Game &game) const
{
    switch (this->from)
    {
    case Cell::a1:
        game.castling_flags &= CastlingRights::WhiteKing ^ CastlingRights::All;
        break;
    case Cell::a8:
        game.castling_flags &= CastlingRights::WhiteQueen ^ CastlingRights::All;
        break;
    case Cell::h1:
        game.castling_flags &= CastlingRights::BlackKing ^ CastlingRights::All;
        break;
    case Cell::h8:
        game.castling_flags &= CastlingRights::BlackQueen ^ CastlingRights::All;
        break;
    default:
        break;
    }
}

void Chess::MoveKingFirst::special(Game &game) const
{
    switch (this->from)
    {
    case Cell::e1:
        game.castling_flags &= CastlingRights::WhiteAll ^ CastlingRights::All;
        break;
    case Cell::e8:
        game.castling_flags &= CastlingRights::BlackAll ^ CastlingRights::All;
        break;
    default:
        break;
    }
}

bool Chess::Game::isKingInCheck(Color kingColor) const
{
    // Find the king's position on the board
    Cell kingPosition;
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Cell cell = makeCell(r, c);
            const Piece *piece = next_board[cell];
            if (piece && (piece->color == kingColor) && dynamic_cast<const King *>(piece))
            {
                kingPosition = cell;
                break;
            }
        }
    }

    // Check if any opponent piece can attack the king
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Cell cell = makeCell(r, c);
            const Piece *opponentPiece = next_board[cell];
            if (opponentPiece && (opponentPiece->color != kingColor))
            {
                std::vector<std::unique_ptr<Move>> possibleMoves = opponentPiece->getRelativeMoves(*this, cell);
                for (const auto &opponentMove : possibleMoves)
                {
                    if (opponentMove->to == kingPosition)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void Chess::MoveCastling::special(Game &game) const
{
    if (castlingType == CastlingType::KingSide)
    {
        Cell rookFrom = makeCell(row(from), 7); // h-file rook
        Cell rookTo = makeCell(row(from), 5);   // f-file
        game.board[rookTo] = game.board[rookFrom];
        game.board[rookFrom] = nullptr;
    }
    else if (castlingType == CastlingType::QueenSide)
    {
        Cell rookFrom = makeCell(row(from), 0); // a-file rook
        Cell rookTo = makeCell(row(from), 3);   // d-file
        game.board[rookTo] = game.board[rookFrom];
        game.board[rookFrom] = nullptr;
    }

    MoveKingFirst(from, to).special(game);
}

bool Chess::Game::isCellAttacked(Cell cell, Color color) const
{
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Cell attacker_cell = makeCell(r, c);
            const Piece *opponentPiece = next_board[attacker_cell];
            if (opponentPiece && opponentPiece->color != color)
            {
                std::vector<std::unique_ptr<Move>> possibleMoves = opponentPiece->getRelativeMoves(*this, attacker_cell);
                for (const auto &move : possibleMoves)
                {
                    if (move->to == cell)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
