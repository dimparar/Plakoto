#include "stdafx.h"
#include "Board.h"
#include <numeric>

void Board::initVariables()
{


}

void Board::initCheckersOnPosition()
{
    
}

void Board::initPositions()
{
    int j = 1;
    int k = 24;
    int i = 57;

    while (i > 34)
    {
        i -= 4;
        this->positions[j] = i;
        this->positions[k] = i;
        k--;
        j++;
    }

    i = 27;
    while (i > 0 && j < 13)
    {
        i -= 4;
        this->positions[j] = i;
        this->positions[k] = i;
        k--;
        j++;
    }

}

int Board::evaluate()
{
    std::vector<int> free_white_pos;
    std::vector<int> free_black_pos;
    for (auto pos : this->checkersOnPosition)
    {
        if (pos.second.size() == 1 && pos.first != 25 && pos.first != 0)
        {
            if (pos.second.back()->getColor() == BLACK)
            {
                free_black_pos.push_back(pos.first);
            }
            if (pos.second.back()->getColor() == WHITE)
            {
                free_white_pos.push_back(pos.first);
            }
        }
    }

    std::map<int, int> pos_value_black;
    pos_value_black[1] = 2400;
    pos_value_black[2] = 2400;

    std::map<int, int> pos_value_white;
    pos_value_white[24] = 2400;
    pos_value_white[23] = 2400;

    int sum_free_white = 0;
    int sum_free_black = 0;

    for (auto pos_black : free_black_pos)
    {
        if (pos_black == 1 || pos_black == 2)
        {
            sum_free_black -= pos_value_black[pos_black];
        }
        else
        {
            sum_free_black -= 1000;
        }
    }

    for (auto pos_white : free_white_pos)
    {
        if (pos_white == 1 || pos_white == 2)
        {
            sum_free_white -= pos_value_white[pos_white];
        }
        else
        {
            sum_free_white -= 1000;
        }
    }

    /*
    * Value the checkers that we beared off in the current state
    */
    std::vector<int> sums_bear_off_black = {0, 0, 0, 0, 0, 0};
    std::vector<int> sums_bear_off_white = {0, 0, 0, 0, 0, 0};
    int beared_off_black = 0;
    int beared_off_white = 0;
    if (this->getColorPhase(BLACK) == BEAR_OFF)
    {
        for (auto checker : this->checkersBlack)
        {
            if (checker->getPosition() > 18 && checker->getPosition() < 25)
            {
                int temp_position = 24 - checker->getPosition();
                sums_bear_off_black[temp_position]++;
            }
            else
            {
                beared_off_black++;
            }
        }
    }
    else if (this->getColorPhase(WHITE) == BEAR_OFF)
    {
        for (auto checker : this->checkersWhite)
        {
            if (checker->getPosition() > 0 && checker->getPosition() < 7)
            {
                int temp_position = checker->getPosition() - 1;
                sums_bear_off_white[temp_position]++;
            }
            else
            {
                beared_off_white++;
            }
        }
    }

    int sum_of_elem_black_bear_off = 0;
    int sum_of_elem_white_bear_off = 0;
    int factor = 120;
    for (int i = 0; i <= 5; i++)
    {
        sum_of_elem_black_bear_off += factor * sums_bear_off_black[i];
        sum_of_elem_white_bear_off += factor * sums_bear_off_white[i];
        factor -= 20;
    }
        
    int sum_crucial_eating_black = 0;
    for (auto checker : this->checkersBlack)
    {
        if (checker->getPosition() == 1 && this->checkersOnPosition[1].back()->getColor() == WHITE)
        {
            sum_crucial_eating_black = -100000;
            break;
        }
    }

    int sum_crucial_eating_white = 0;
    for (auto checker : this->checkersWhite)
    {
        if (checker->getPosition() == 1 && this->checkersOnPosition[1].back()->getColor() == BLACK)
        {
            sum_crucial_eating_white = -100000;
            break;
        }
    }

    int eated_black = 0;
    for (auto checker : this->checkersBlack)
    {
        if (this->checkersOnPosition[checker->getPosition()].back()->getColor() != checker->getColor())
        {
            eated_black++;
        }
    }

    int eated_white = 0;
    for (auto checker : this->checkersWhite)
    {
        if (this->checkersOnPosition[checker->getPosition()].back()->getColor() != checker->getColor())
        {
            eated_white++;
        }
    }

    std::vector<int> black_continuous_doors;
    int position_black = -1;
    for (auto pos : this->checkersOnPosition)
    {
        if (pos.second.size() > 0 && pos.first != 25)
        {
            if (pos.second.back()->getColor() == BLACK && pos.second.size() >= 2)
            {
                if (position_black == pos.first - 1)
                {
                    black_continuous_doors.back()++;
                }
                else
                {
                    black_continuous_doors.push_back(1);
                }
                position_black = pos.first;
            }
            else
            {
                position_black = -1;
            }
        }
    }

    int sum_elem_black_continuous_doors = 0;
    for (auto door : black_continuous_doors)
    {
        sum_elem_black_continuous_doors += std::pow(door, door);
    }

    std::vector<int> white_continuous_doors;
    int position_white = -1;
    for (auto pos : this->checkersOnPosition)
    {
        if (pos.second.size() > 0 && pos.first != 0)
        {
            if (pos.second.back()->getColor() == WHITE && pos.second.size() >= 2)
            {
                if (position_white == pos.first - 1)
                {
                    white_continuous_doors.back()++;
                }
                else
                {
                    white_continuous_doors.push_back(1);
                }
                position_white = pos.first;
            }
            else
            {
                position_white = -1;
            }
        }
    }

    int sum_elem_white_continuous_doors = 0;
    for (auto door : white_continuous_doors)
    {
        sum_elem_white_continuous_doors += std::pow(door, door);
    }

    int sum_door_size_black = 0;
    for (auto pos : this->checkersOnPosition)
    {
        if (!pos.second.size() > 1 && pos.second.size() < 5)
        {
            if (pos.second.back()->getColor() == BLACK)
            {
                sum_door_size_black += pos.second.size() * 500;
            }
        }
    }

    int sum_door_size_white = 0;
    for (auto pos : this->checkersOnPosition)
    {
        if (!pos.second.size() > 1 && pos.second.size() < 5)
        {
            if (pos.second.back()->getColor() == WHITE)
            {
                sum_door_size_white += pos.second.size() * 500;
            }
        }
    }

    // stay close
    int sum_checkers_too_far_black = 0;
    int last_pos_black = 0;

    int sum_checkers_too_far_white = 0;
    int last_pos_white = 0;

    for (int pos = 1; pos < 25; pos++)
    {
        if (!this->checkersOnPosition[pos].empty())
        {
            if (this->checkersOnPosition[pos].back()->getColor() == BLACK)
            {
                if (last_pos_black == 0)
                {
                    last_pos_black = pos;
                }
                else
                {
                    if (pos - last_pos_black > 4)
                    {
                        sum_checkers_too_far_black -= (pos - last_pos_black) * 500;
                    }

                    last_pos_black = pos;
                }
            }

            if (this->checkersOnPosition[pos].back()->getColor() == WHITE)
            {
                if (last_pos_white == 0)
                {
                    last_pos_white = pos;
                }
                else
                {
                    if (pos - last_pos_white > 4)
                    {
                        sum_checkers_too_far_white -= (pos - last_pos_white) * 500;
                    }

                    last_pos_white = pos;
                }
            }
        }
    }

    // enemy too close
    int sum_close_enemy_black = 0;
    int last_pos_checker_black = 0;

    for (int pos = 1; pos < 25; pos++)
    {
        if (!this->checkersOnPosition[pos].empty())
        {
            if (last_pos_checker_black == 0)
            {
                if (this->checkersOnPosition[pos].size() == 1)
                {
                    if (this->checkersOnPosition[pos].back()->getColor() == BLACK)
                    {
                        last_pos_checker_black = pos;
                    }
                }
            }
            else
            {
                if (this->checkersOnPosition[pos].back()->getColor() == WHITE)
                {
                    if (pos - last_pos_checker_black < 7)
                    {
                        sum_close_enemy_black -= (pos - last_pos_checker_black) * 1000;
                    }
                    last_pos_checker_black = 0;
                }
            }
        }
    }

    int sum_close_enemy_white = 0;
    int last_pos_checker_white = 0;
    int pos = 24;
    while (pos > 0)
    {
        if (!this->checkersOnPosition[pos].empty())
        {
            if (last_pos_checker_white == 0)
            {
                if (this->checkersOnPosition[pos].size() == 1)
                {
                    if (this->checkersOnPosition[pos].back()->getColor() == WHITE)
                    {
                        last_pos_checker_white = pos;
                    }
                }
            }
            else
            {
                if (this->checkersOnPosition[pos].back()->getColor() == WHITE)
                {
                    if (pos - last_pos_checker_black < 7)
                    {
                        sum_close_enemy_white -= (last_pos_checker_white - pos ) * 1000;
                    }
                    last_pos_checker_white = 0;
                }
            }
        }

        pos--;
    }

    int sum_black = sum_close_enemy_black + sum_door_size_black + sum_checkers_too_far_black + sum_crucial_eating_black + 5000*eated_white + 300*beared_off_black + sum_of_elem_black_bear_off + sum_elem_black_continuous_doors + sum_free_black;
    int sum_white = sum_close_enemy_white + sum_door_size_white + sum_checkers_too_far_white + sum_crucial_eating_white + 5000*eated_black + 300*beared_off_white + sum_of_elem_white_bear_off + sum_elem_white_continuous_doors + sum_free_white;
    
    return sum_black - sum_white;
}

Board::Board(std::vector<Checker*> checkersBlack, std::vector<Checker*> checkersWhite)
{
    this->tie = false;
    this->colored_table = false;
    this->checkersBlack = checkersBlack;
    this->checkersWhite = checkersWhite;  
    this->blackPhase = STANDARD;
    this->whitePhase = STANDARD;

    this->blackToBearOff = 0;
    this->whiteToBearOff = 0;

    this->initPositions();
}

Board::Board(const Board* board)
{
    this->table = board->table;
    this->positions = board->positions;
    this->blackPhase = board->blackPhase;
    this->whitePhase = board->whitePhase;

    for (auto i : board->checkersOnPosition)
    {
        for (auto j : i.second)
        {
            this->checkersOnPosition[i.first].push_back(new Checker(j));
        }
    }

    for (auto i : this->checkersOnPosition)
    {
        for (auto j : i.second)
        {
            if (j->getColor() == WHITE)
            {
                this->checkersWhite.push_back(j);
            }
            else
            {
                this->checkersBlack.push_back(j);
            }
        }
    }

    this->lastMove = board->lastMove;
    this->moveChecker = board->moveChecker;

}

Board::~Board()
{
    for (auto i : this->checkersBlack)
    {
        if (i)
        {
            delete i;
        }
    }
    this->checkersBlack.clear();

    for (auto i : this->checkersWhite)
    {
        if (i)
        {
            delete i;
        }
    }
    this->checkersWhite.clear();

    delete this->lastMove;

}

void Board::createTable()
{
    this->table.push_back("_________________________________________________________");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("| 13  14  15  16  17  18  |   | 19  20  21  22  23  24  |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |BAR|                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("| 12  11  10   9   8   7  |   |  6   5   4   3   2   1  |");
    this->table.push_back("|_________________________|___|_________________________|");

    
}

void Board::makeMove(Move* move, Board* board)
{
    board->moveChecker = true;
    board->lastMove = move;

    if (!board->checkersOnPosition.empty())
    {
        if (!board->checkersOnPosition[move->getFromPosition()].empty())
        {
            board->checkersOnPosition[move->getFromPosition()].back()->setPosition(move->getToPosition()); // updates checker position
        }
    }
    
}

void Board::makeSecondMove(Move* move, Board* board)
{
    board->lastMove = move;

    if (move->getFromPosition_1() != -1)
    {
        if (!board->checkersOnPosition[move->getFromPosition_1()].empty() && move->getFromPosition_1() != move->getFromPosition())
        {
            board->checkersOnPosition[move->getFromPosition_1()].back()->setPosition(move->getToPosition_1());
            // updates second checker position not in the same col with the first position
        }
        if (board->checkersOnPosition[move->getFromPosition_1()].size() >= 2 && move->getFromPosition_1() == move->getFromPosition())
        {
            if (!board->checkersOnPosition[move->getFromPosition_1()].empty())
            {
                board->checkersOnPosition[move->getFromPosition_1()].at(board->checkersOnPosition[move->getFromPosition_1()].size() - 2)->setPosition(move->getToPosition_1());
            }
        }

    }


}


bool Board::isValidMove(Move* move, Dice* dice, int turn)
{
    if (!this->checkersOnPosition[move->getToPosition_1()].empty())
    {
        if (this->checkersOnPosition[move->getToPosition_1()].back()->getColor() != this->checkersOnPosition[move->getFromPosition_1()].back()->getColor())
        {// here we have the top checker of the column with the same color of the checker that we want to move

            if (this->checkersOnPosition[move->getToPosition_1()].size() > 1)
            {// here we have only one checker with different color in the to_position column. So we "eat" it
                return false;
            }
        }
    }

    // first check if the position doesn't have any checkers
    if (!this->checkersOnPosition[move->getToPosition()].empty())
    {
        if (this->checkersOnPosition[move->getToPosition()].back()->getColor() != this->checkersOnPosition[move->getFromPosition()].back()->getColor())
        {// here we have the top checker of the column with the same color of the checker that we want to move

            if (this->checkersOnPosition[move->getToPosition()].size() > 1)
            {// here we have only one checker with different color in the to_position column. So we "eat" it
                return false;
            }
        }
    }

    //We must check also for the number of moves if there right according to the indexes of the dices
 
    if (std::abs(move->getFromPosition() - move->getToPosition()) == dice->getDice1() + dice->getDice2() && !dice->getPlayedDice1() && !dice->getPlayedDice2())
    {
        dice->setPlayedDice1(true);
        dice->setPlayedDice2(true);
    }
    else if (std::abs(move->getFromPosition() - move->getToPosition()) == dice->getDice1() && !dice->getPlayedDice1())
    {
        dice->setPlayedDice1(true);
    }
    else if (std::abs(move->getFromPosition() - move->getToPosition()) == dice->getDice2() && !dice->getPlayedDice2())
    {
        dice->setPlayedDice2(true);
    }
    else
    {
        return false;
    }

    return true;
}

void Board::updateCheckersOnPosition()
{
    /*for (auto i : this->checkersBlack)
    {
        this->checkersOnPosition[i->getPosition()].push_back(i);
    }
    
    for (auto i : this->checkersWhite)
    {
        this->checkersOnPosition[i->getPosition()].push_back(i);
    }*/
}

void Board::updateUserMove(int color, Board* board)
{
    int checkerID = -1;
    int checkerID_1 = -1;

    if (board->lastMove && board->getLastMove()->getFromPosition() != -1)
    {
        if (board->getLastMove()->getFromPosition() == board->getLastMove()->getFromPosition_1())
        {
            checkerID = board->checkersOnPosition[board->getLastMove()->getFromPosition()].back()->getId();

            checkerID_1 = board->checkersOnPosition[board->getLastMove()->getFromPosition_1()][board->checkersOnPosition[board->getLastMove()->getFromPosition_1()].size() - 2]->getId();
        }
        else
        {
            checkerID = board->checkersOnPosition[board->getLastMove()->getFromPosition()].back()->getId();

            if (board->getLastMove()->getFromPosition_1() != -1)
            {
                checkerID_1 = board->checkersOnPosition[board->getLastMove()->getFromPosition_1()].back()->getId();
            }
        }
    }

    if (board->moveChecker)
    {
        board->moveChecker = false;

        size_t size = board->checkersOnPosition[board->lastMove->getFromPosition()].size();
        size_t size_table_item = board->checkersOnPosition[board->lastMove->getFromPosition()].size();

        if (size <= 6)
        {
            size_table_item -= 1;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int count = 0;

                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(board->positions[board->lastMove->getFromPosition()], 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(board->positions[board->lastMove->getFromPosition()], 1, " ");
            }
        }
        else if (size <= 12)
        {
            size_table_item -= 7;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 1;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 1;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
        }
        else if (size < 17)
        {
            size_table_item -= 13;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 2;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 2;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
        }

        if (board->lastMove->getFromPosition_1() != -1)
        {
            size_t size_1 = board->checkersOnPosition[board->lastMove->getFromPosition_1()].size();
            size_t size_table_item_1 = board->checkersOnPosition[board->lastMove->getFromPosition_1()].size();

            if (size_1 <= 6)
            {
                size_table_item_1 -= 1;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(board->positions[board->lastMove->getFromPosition_1()], 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(board->positions[board->lastMove->getFromPosition_1()], 1, " ");
                }
            }
            else if (size_1 <= 12)
            {
                size_table_item_1 -= 7;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
            }
            else if (size_1 < 17)
            {
                size_table_item_1 -= 13;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 2;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 2;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
            }
            checkerID = -1;
            checkerID_1 = -1;
        }
    }
}

void Board::updateCheckers(int color, Board* board)
{
    std::vector<Checker*> checkers;
    if (color == WHITE)
    {
        checkers = board->checkersWhite;
    }
    else
    {
        checkers = board->checkersBlack;
    }

    int checkerID = -1;
    int checkerID_1 = -1;


    if (board->lastMove && board->getLastMove()->getFromPosition() != -1)
    {
        if (board->getLastMove()->getFromPosition() == board->getLastMove()->getFromPosition_1())
        {

            checkerID = board->checkersOnPosition[board->getLastMove()->getFromPosition()].back()->getId();

            
            checkerID_1 = board->checkersOnPosition[board->getLastMove()->getFromPosition_1()][board->checkersOnPosition[board->getLastMove()->getFromPosition_1()].size() - 2]->getId();
        }
        else
        {

            checkerID = board->checkersOnPosition[board->getLastMove()->getFromPosition()].back()->getId();

            if (board->getLastMove()->getFromPosition_1() != -1)
            {
                checkerID_1 = board->checkersOnPosition[board->getLastMove()->getFromPosition_1()].back()->getId();
            }
        }
    }


    int test = 0;

    for (auto i : checkers)
    {
        bool already_on_position = false;

        // search for the checker -> if it is on position skip ...
        for (auto j : board->checkersOnPosition[i->getPosition()])
        {
            if (i == j)
            {// search if the checker is in the old position
                already_on_position = true;
                break;
            }
        }

        if (!already_on_position)
        {
            if (board->getColorPhase(color) == BEAR_OFF && (i->getPosition() == 25 || i->getPosition() == 0))
            {
                board->checkersOnPosition[i->getPosition()].push_back(i);
            }
            else
            {
                size_t size = board->checkersOnPosition[i->getPosition()].size();
                size_t size_table_item = board->checkersOnPosition[i->getPosition()].size();

                if (size < 6)
                {
                    if (i->getPosition() < 13)
                    {
                        int table_item = 15 - size_table_item;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        board->table[table_item].replace(board->positions[i->getPosition()], 1, i->render());
                        test++;
                    }
                    else
                    {
                        int table_item = 3 + size_table_item;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        board->table[table_item].replace(board->positions[i->getPosition()], 1, i->render());
                        test++;
                    }
                }
                else if (size < 12)
                {
                    size_table_item -= 6;
                    if (i->getPosition() < 13)
                    {
                        int table_item = 15 - size_table_item;
                        int table_position = board->positions[i->getPosition()] + 1;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                    else
                    {
                        int table_item = 3 + size_table_item;
                        int table_position = board->positions[i->getPosition()] + 1;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                }
                else if (size < 17)
                {
                    size_table_item -= 12;
                    if (i->getPosition() < 13)
                    {
                        int table_item = 15 - size_table_item;
                        int table_position = board->positions[i->getPosition()] + 2;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                    else
                    {
                        int table_item = 3 + size_table_item;
                        int table_position = board->positions[i->getPosition()] + 2;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                }
            }
        }
    }


    if (board->moveChecker)
    {

        board->moveChecker = false;

        size_t size = board->checkersOnPosition[board->lastMove->getFromPosition()].size();
        size_t size_table_item = board->checkersOnPosition[board->lastMove->getFromPosition()].size();

        if (size <= 6)
        {
            size_table_item -= 1;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int count = 0;

                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(board->positions[board->lastMove->getFromPosition()], 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(board->positions[board->lastMove->getFromPosition()], 1, " ");
            }
        }
        else if (size <= 12)
        {
            size_table_item -= 7;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 1;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 1;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
        }
        else if (size < 17)
        {
            size_table_item -= 13;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 2;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 2;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
        }


        if (board->lastMove->getFromPosition_1() != -1)
        {
            size_t size_1 = board->checkersOnPosition[board->lastMove->getFromPosition_1()].size();
            size_t size_table_item_1 = board->checkersOnPosition[board->lastMove->getFromPosition_1()].size();

            if (size_1 <= 6)
            {
                size_table_item_1 -= 1;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(board->positions[board->lastMove->getFromPosition_1()], 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(board->positions[board->lastMove->getFromPosition_1()], 1, " ");
                }
            }
            else if (size_1 <= 12)
            {
                size_table_item_1 -= 7;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
            }
            else if (size_1 < 17)
            {
                size_table_item_1 -= 13;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 2;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 2;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
            }
            checkerID = -1;
            checkerID_1 = -1;
        }
    }

    // set blackToBearOff/whiteToBearOff
    int counter_1 = 0;
    for (auto i : checkers)
    {
        if (i->getPosition() == 0 || i->getPosition() == 25)
        {
            counter_1++;
        }
    }

    if (color == BLACK)
    {
        board->blackToBearOff = counter_1;
    }
    else
    {
        board->whiteToBearOff = counter_1;
    }

}

void Board::printTable()
{

    for (auto i : this->table)
    {
        std::cout << i << "\n";
    }
}

bool Board::getMoveChecker()
{
    return this->moveChecker;
}

Move* Board::getLastMove()
{
    return this->lastMove;
}

bool Board::canCheckerMove(Checker* checker)
{
   
    if (checker->getPosition() != 25 && checker->getPosition() != 0)
    {
        if (!this->checkersOnPosition[checker->getPosition()].empty())
        {
            if (this->checkersOnPosition[checker->getPosition()].back() == checker)
            {// checking if the given checker is at the top of the column, and is the same color as the one at the top of the color
                return true;
            }
        }
    }
    
    return false;
}

bool Board::canSecondCheckerMove(Checker* checker)
{
    if (this->checkersOnPosition[checker->getPosition()].size() >= 2)
    {
        if (this->checkersOnPosition[checker->getPosition()].at(this->checkersOnPosition[checker->getPosition()].size() - 2) == checker)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

std::vector<Board*> Board::getChildren(int color, Dice* dice, Board* board)
{
    std::vector<Board*> children;
    bool one_dice_cannot_be_played = true;

    //first we check if the two dice are not the same

    int from_multiple_pos;// it will tell us if we are white, then we must go backwards

    int from_multiple_pos1;
    int from_multiple_pos2;

    if (color == WHITE)
    {
        from_multiple_pos = -1 * (dice->getDice1() + dice->getDice2());

        from_multiple_pos1 = -1 * (dice->getDice1());
        from_multiple_pos2 = -1 * (dice->getDice2());
    }
    else
    {
        from_multiple_pos = dice->getDice1() + dice->getDice2();

        from_multiple_pos1 = dice->getDice1();
        from_multiple_pos2 = dice->getDice2();
    }

    // In this first case, we check if the checker can move the sum(dice1,dice2)
    for (auto i : board->getCheckers(color))
    {
        if (this->canCheckerMove(i))
        {
            if (this->isValidMoveAI(i->getPosition() + from_multiple_pos, i))
            {
                int to_position = i->getPosition() + from_multiple_pos;
                
                if (! ((i->getPosition() + from_multiple_pos1 > 24 || i->getPosition() + from_multiple_pos1 < 1)
                    || (i->getPosition() + from_multiple_pos2 > 24 || i->getPosition() + from_multiple_pos2 < 1)) )
                {
                    if (color == BLACK)
                    {
                        if (to_position > 25)
                        {
                            to_position = 25;
                        }
                    }
                    else
                    {
                        if (to_position < 0)
                        {
                            to_position = 0;
                        }
                    }

                    Board* child = new Board(board);
                    Move* move = new Move(i->getPosition(), to_position);
                    this->makeMove(move, child);
                    this->updateCheckers(color, child);
                    child->updatePhase(color);
                    children.push_back(child);
                    one_dice_cannot_be_played = false;
                }
            }

            //In this second case, we search for the most possible moves that the checker can do
            /*
            * 1.We search for every possible combination of two checkers with the two different indexes of the dices
            * 2.We must search the case where he cannot make use of one of the two checkers.That's the case of the one_dice_cannot_be_played
            */

            for (auto j : board->getCheckers(color))
            {
                /*if (board->getColorPhase(color) != BEAR_OFF &&
                    ((j->getPosition() + from_multiple_pos1 <= 24 && j->getPosition() + from_multiple_pos1 >= 1) 
                     || (j->getPosition() + from_multiple_pos2 <= 24 && j->getPosition() + from_multiple_pos2 >= 1)))*/
               
                if (j != i)
                {
                    bool check;
                    if (i->getPosition() == j->getPosition())
                    {
                        check = this->canSecondCheckerMove(j);
                    }
                    else
                    {
                        check = this->canCheckerMove(j);
                    }

                    if (check) // checks if j is under i
                    {
                        // now we check if the two dices can make use of the index of the dice

                        if (this->isValidMoveAI(i->getPosition() + from_multiple_pos1, i))
                        {
                            // Here the bot can play the two checkers with the first checker follows the index of the second dice and vice versa

                            int to_position_1 = i->getPosition() + from_multiple_pos1;

                            if (color == BLACK)
                            {
                                if (to_position_1 > 25)
                                {
                                    to_position_1 = 25;
                                }
                            }
                            else
                            {
                                if (to_position_1 < 0)
                                {
                                    to_position_1 = 0;
                                }
                            }


                            Board* child = new Board(board);
                            Move* move = new Move(i->getPosition(), to_position_1);

                            child->makeMove(move, child);

                            // checks phase
                            child->updatePhase(color);

                            int to_position_2;
                            if (child->isValidMoveAI(j->getPosition() + from_multiple_pos2, j))
                            {
                                to_position_2 = j->getPosition() + from_multiple_pos2;

                                if (color == BLACK)
                                {
                                    if (to_position_2 > 25)
                                    {
                                        to_position_2 = 25;
                                    }
                                }
                                else
                                {
                                    if (to_position_2 < 0)
                                    {
                                        to_position_2 = 0;
                                    }
                                }

                                move->setFromPosition_1(j->getPosition());
                                move->setToPosition_1(to_position_2);

                                child->makeSecondMove(move, child);

                                this->updateCheckers(color, child);
                                children.push_back(child);
                                one_dice_cannot_be_played = false;
                            }

                        }

                        if (this->isValidMoveAI(i->getPosition() + from_multiple_pos2, i))
                        {
                            //Here the bot can play the two checkers with the first checker follows the index of the second dice and vice versa

                            int to_position_1 = i->getPosition() + from_multiple_pos2;

                            if (color == BLACK)
                            {
                                if (to_position_1 > 25)
                                {
                                    to_position_1 = 25;
                                }
                            }
                            else
                            {
                                if (to_position_1 < 0)
                                {
                                    to_position_1 = 0;
                                }
                            }

                            Board* child = new Board(board);
                            Move* move = new Move(i->getPosition(), to_position_1);

                            this->makeMove(move, child);

                            child->updatePhase(color);

                            int to_position_2;
                            if (child->isValidMoveAI(j->getPosition() + from_multiple_pos1, j))
                            {
                                to_position_2 = j->getPosition() + from_multiple_pos1;

                                if (color == BLACK)
                                {
                                    if (to_position_2 > 25)
                                    {
                                        to_position_2 = 25;
                                    }
                                }
                                else
                                {
                                    if (to_position_2 < 0)
                                    {
                                        to_position_2 = 0;
                                    }
                                }

                                move->setFromPosition_1(j->getPosition());
                                move->setToPosition_1(to_position_2);

                                child->makeSecondMove(move, child);
                                this->updateCheckers(color, child);

                                children.push_back(child);
                                one_dice_cannot_be_played = false;
                            }

                        }
                    }
                }
            }
        }
    }

    if (one_dice_cannot_be_played)
    {
        // here we play only one of the two dice
        for (auto i : board->getCheckers(color))
        {
            /*
            * Check if the checker can play the 1st dice
            */
            if (this->canCheckerMove(i))
            {
                if (this->isValidMoveAI(i->getPosition() + from_multiple_pos1, i))
                {
                    Board* child = new Board(this);
                    Move* move = new Move(i->getPosition(), i->getPosition() + from_multiple_pos1);
                    this->makeMove(move, child);
                    child->updatePhase(color);

                    this->updateCheckers(color, child);
                    children.push_back(child);
                }

                /*
                * Check if the checker can play the 2nd dice
                */
                if (this->isValidMoveAI(i->getPosition() + from_multiple_pos2, i))
                {
                    Board* child = new Board(this);
                    Move* move = new Move(i->getPosition(), i->getPosition() + from_multiple_pos2);
                    this->makeMove(move, child);
                    child->updatePhase(color);

                    this->updateCheckers(color, child);
                    children.push_back(child);
                }
            }
        }
    }

    return children;
}

void Board::updatePhase(int color)
{
    // set phase color if all checkers are in the exit table
    if (this->getColorPhase(color) == STANDARD)
    {
        int counter = 0;
        bool can_bear_off = false;

        for (auto i : this->getCheckers(color))
        {
            if (color == BLACK)
            {
                if (i->getPosition() > 18)
                {
                    counter++;
                }
            }
            else
            {
                if (i->getPosition() < 7)
                {
                    counter++;
                }
            }
        }

        if (counter == 15)
        {
            if (color == BLACK)
            {
                this->blackPhase = BEAR_OFF;
            }
            else
            {
                this->whitePhase = BEAR_OFF;
            }
        }
    }
}

bool Board::isValidMoveAI(int position, Checker* checker)
{
    if (isValidToPosition(position, checker))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::isValidToPosition(int position, Checker* checker)
{
    if ((position < 1 || position > 24) && this->getColorPhase(checker->getColor()) == BEAR_OFF)
    {
        return true;
    }

    if ((position < 1 || position > 24) && this->getColorPhase(checker->getColor()) == STANDARD)
    {
        if (checker->getColor() == BLACK)
        {
            if (this->blackToBearOff == 14 && checker->getPosition() <= 18)
            {
                return true;
            }
        }
        else
        {
            if (this->whiteToBearOff == 14 && checker->getPosition() >= 7)
            {
                return true;
            }
        }

        return false;
    }

    // first check if the position doesn't have any checkers
    if (this->checkersOnPosition[position].empty())
    {
        return true;
    }
    else if (this->checkersOnPosition[position].back()->getColor() == checker->getColor())
    {// here we have the top checker of the column with the same color of the checker that we want to move
        return true;
    }
    else if (this->checkersOnPosition[position].size() == 1)
    {// here we have only one checker with different color in the to_position column. So we "eat" it
        return true;
    }
    else
    {// here we have a lot of checkers with the opposite color in the same row
        return false;
    }
}

std::vector<Checker*> Board::getCheckers(int color)
{
    if (color == WHITE)
    {
        return this->checkersWhite;
    }
    else
    {
        return this->checkersBlack;
    }
}

std::map<int, std::vector<Checker*>> Board::getCheckersOnPosition()
{
    return this->checkersOnPosition;
}

int Board::searchForID(std::vector<Checker*> checkers, int id, int color)
{
    int count = 0;
    for (auto i : checkers)
    {
        if (i->getId() == id && i->getColor() == color)
        {
            return count;
        }
        count++;
    }
    return -1;
}

int Board::getColorPhase(int color)
{
    if (color == BLACK)
    {
        return this->blackPhase;
    }
    else
    {
        return this->whitePhase;
    }
}

bool Board::getTie()
{
    return this->tie;
}

bool Board::isTerminal()
{
    int sum_b = 0;
    int sum_w = 0;

    int counter_end_game = 0;

    for (auto black : this->checkersBlack)
    {
        if (black->getPosition() == 25)
        {
            sum_b++;
        }

        if (black->getPosition() == 1)
        {
            if (this->checkersOnPosition[1].back()->getColor() == WHITE)
            {
                counter_end_game++;
            }
        }
    }

    for (auto white : this->checkersWhite)
    {
        if (white->getPosition() == 0)
        {
            sum_w++;
        }

        if (white->getPosition() == 24)
        {
            if (this->checkersOnPosition[24].back()->getColor() == BLACK)
            {
                counter_end_game++;
            }
        }
    }

    if (counter_end_game == 2)
    {
        this->tie = true;
        return true;
    }


    if (sum_w == 15 || sum_b == 15)
    {
        return true;
    }

    counter_end_game = 0;

    return false;
}
