#pragma once

namespace Chess
{
	struct Coordinate
	{
	private:
		char m_file;
		int m_rank;

	public:
		Coordinate();
		Coordinate(char file, int rank);

	public:
		char get_File() const { return m_file; }
		int get_Rank() const { return m_rank; }

	public:
		Coordinate& operator=(const Coordinate& other);
		bool operator==(const Coordinate& other) const;
	};
}
