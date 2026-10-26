#pragma once

#include "Game.h"

#include <iostream>
#include <limits>

class TicTacToe : public Game
{
public:
	TicTacToe()
		: m_board{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
		, m_currentPlayer(0)
	{
	}

	bool IsGameOver() const override
	{
		char winner = ' ';
		return HasWinner(winner) || IsBoardFull();
	}

	void TakeTurn() override
	{
		while (true)
		{
			int position = 0;
			std::cout << "Player " << (m_currentPlayer + 1) << " (" << GetMarkForCurrentPlayer()
				<< "), enter position (1-9): ";

			if (!(std::cin >> position))
			{
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Invalid input. Please enter a number from 1 to 9.\n";
				continue;
			}

			if (position < 1 || position > 9)
			{
				std::cout << "Invalid position. Please enter a number from 1 to 9.\n";
				continue;
			}

			const int index = position - 1;
			if (m_board[index] != ' ')
			{
				std::cout << "That position is already taken. Choose another.\n";
				continue;
			}

			m_board[index] = GetMarkForCurrentPlayer();
			break;
		}

		if (!IsGameOver())
		{
			m_currentPlayer = 1 - m_currentPlayer;
		}
	}

	void Display() const override
	{
		std::cout << "\n";
		for (int row = 0; row < 3; ++row)
		{
			const int start = row * 3;
			std::cout << " " << m_board[start] << " | " << m_board[start + 1] << " | " << m_board[start + 2] << "\n";
			if (row < 2)
			{
				std::cout << "---+---+---\n";
			}
		}

		char winner = ' ';
		if (HasWinner(winner))
		{
			std::cout << "Player " << (winner == 'X' ? 1 : 2) << " wins!\n\n";
		}
		else if (IsBoardFull())
		{
			std::cout << "It's a tie!\n\n";
		}
		else
		{
			std::cout << "Player " << (m_currentPlayer + 1) << "'s turn (" << GetMarkForCurrentPlayer() << ")\n\n";
		}
	}

private:
	bool HasWinner(char& winner) const
	{
		static const int winningLines[8][3] =
		{
			{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
			{0, 3, 6}, {1, 4, 7}, {2, 5, 8},
			{0, 4, 8}, {2, 4, 6}
		};

		for (const auto& line : winningLines)
		{
			const char first = m_board[line[0]];
			if (first != ' ' && first == m_board[line[1]] && first == m_board[line[2]])
			{
				winner = first;
				return true;
			}
		}

		winner = ' ';
		return false;
	}

	bool IsBoardFull() const
	{
		for (char space : m_board)
		{
			if (space == ' ')
			{
				return false;
			}
		}

		return true;
	}

	char GetMarkForCurrentPlayer() const
	{
		return (m_currentPlayer == 0) ? 'X' : 'O';
	}

	char m_board[9];
	int m_currentPlayer;
};
