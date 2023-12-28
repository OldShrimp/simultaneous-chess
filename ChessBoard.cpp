#include "ChessBoard.h"
#include <stdexcept>
#include <iostream>

ChessBoard::ChessBoard()
{
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
			board[i][j] = nullptr;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		new Pawn(0, std::pair<int, int>(i, 1), this);
		new Pawn(1, std::pair<int, int>(i, BOARDSIZE - 2), this);
	}
	// add other pieces once implemented

	updatePieces();

	std::cout << "chessboard created\n";
}

ChessBoard::~ChessBoard()
{
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (board[i][j] != nullptr)
				delete board[i][j];
		}
	std::cout << "chessboard destroyed\n";
}


void ChessBoard::addPiece(Piece* p)
{
	auto pos = p->getPosition();
	if (board[pos.first][pos.second] != nullptr)
		throw std::runtime_error("Error: another piece already in target position.");
	board[pos.first][pos.second] = p;
}

void ChessBoard::removePiece(Piece* p)
{
	if (p->team == 0)
		scores.first += p->value;
	else
		scores.second += p->value;

	auto pos = p->getPosition();
	board[pos.first][pos.second] = nullptr;
}

void ChessBoard::movePiece(Piece* p, std::pair<int, int> pos)
{
	auto moves = p->getValidMoves();
	if (std::find(moves.begin(), moves.end(), pos) != moves.end())
	{
		if (p->team == 0)
		{
			currentTurn.p1_destination = pos;
			currentTurn.p1_origin = p->getPosition();
		}
		else
		{
			currentTurn.p2_destination = pos;
			currentTurn.p2_origin = p->getPosition();
		}
	}
	else
		throw std::runtime_error("invalid move");

	if (currentTurn.p1_origin.first != -1 && currentTurn.p2_origin.first != -1)
		nextTurn();
}

void ChessBoard::movePiece(std::pair<int, int> start, std::pair<int, int> fin)
{
	movePiece(board[start.first][start.second], fin);
}

std::vector<std::vector<const Piece*>> ChessBoard::getBoardState()
{
	std::vector<std::vector<const Piece*>> boardstate;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		boardstate.push_back(std::vector<const Piece*>());
		for (int j = 0; j < BOARDSIZE; j++)
		{
			boardstate[i].push_back(board[i][j]);
		}
	}
	return boardstate;
}

std::vector<std::pair<int, int>> ChessBoard::checkCheck(bool t)
{
	// find all pieces that threaten the king, then return their positions
	std::vector<std::pair<int, int>> r;
	return r;
}


void ChessBoard::nextTurn() 
{
	std::vector<Piece*> to_delete;
	auto piece_removal = [&to_delete](Piece* p) { if (std::find(to_delete.begin(), to_delete.end(), p) == to_delete.end()) to_delete.push_back(p); };
	history.push_back(currentTurn);
	auto p1 = board[currentTurn.p1_origin.first][currentTurn.p1_origin.second], p2 = board[currentTurn.p2_origin.first][currentTurn.p2_origin.second];
	// pieces move immediately
	board[currentTurn.p1_origin.first][currentTurn.p1_origin.second] = nullptr;
	board[currentTurn.p2_origin.first][currentTurn.p2_origin.second] = nullptr;

	if (currentTurn.p1_destination == currentTurn.p2_destination) // both pieces are destroyed in a collision
	{
		piece_removal(p1);
		piece_removal(p2);
	}
	else // simply do each move, destroying pieces at destination tile if needed
	{
		if (board[currentTurn.p1_destination.first][currentTurn.p1_destination.second] != nullptr)
			piece_removal(board[currentTurn.p1_destination.first][currentTurn.p1_destination.second]);
		// en passent logic
		else if (p1->type == 'p' && currentTurn.p1_origin.first != currentTurn.p1_destination.first && board[currentTurn.p1_destination.first][currentTurn.p1_origin.second] != nullptr)
			if (board[currentTurn.p1_destination.first][currentTurn.p1_origin.second]->type == 'p'
				&& board[currentTurn.p1_destination.first][currentTurn.p1_origin.second]->team != p1->team) // possible false positive in some cases
				piece_removal(board[currentTurn.p1_destination.first][currentTurn.p1_origin.second]);
		board[currentTurn.p1_destination.first][currentTurn.p1_destination.second] = p1;
		p1->setPosition(currentTurn.p1_destination);

		if (board[currentTurn.p2_destination.first][currentTurn.p2_destination.second] != nullptr)
			piece_removal(board[currentTurn.p2_destination.first][currentTurn.p2_destination.second]);
		// en passent logic
		else if (p2->type == 'p' && currentTurn.p2_origin.first != currentTurn.p2_destination.first && board[currentTurn.p2_destination.first][currentTurn.p2_origin.second] != nullptr)
			if (board[currentTurn.p2_destination.first][currentTurn.p2_origin.second]->type == 'p'
				&& board[currentTurn.p2_destination.first][currentTurn.p2_origin.second]->team != p2->team) // possible false positive in some cases
				piece_removal(board[currentTurn.p2_destination.first][currentTurn.p2_origin.second]);
		board[currentTurn.p2_destination.first][currentTurn.p2_destination.second] = p2;
		p2->setPosition(currentTurn.p2_destination);
	}

	for (auto& i : to_delete)
		delete i;

	currentTurn = turn();

	updatePieces();
	//check for check here, then somehow implement the restricted moves
}

void ChessBoard::updatePieces()
{
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (board[i][j] != nullptr)
				board[i][j]->update();
		}
}