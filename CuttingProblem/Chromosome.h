#pragma once

#include "RectangleDB.h"

#include <vector>

class Chromosome
{
public:
	Chromosome();
	~Chromosome();

	const size_t				Size() const { return m_iRectangleQueue.size(); }

	const int					GetGene(const size_t index) { return m_iRectangleQueue[index]; }
	RectangleF*					GetRectangle(const size_t index) { return m_RectanglePlacement[index]; }
	const RectangleDB&			GetRectangleDB() { return m_RectanglePlacement; }

    bool		                IsPlacement() const { return m_bIsPlacement; }
    void				        SetPlacement(bool bPlacement) { m_bIsPlacement = bPlacement; }

	static Chromosome*			GenerateRandChromosome();

private:
    std::vector<int>			m_iRectangleQueue;
    RectangleDB					m_RectanglePlacement;
    
	float						m_fFitnessValue;
	bool						m_bIsPlacement;

	// not implemented
	Chromosome(const Chromosome&);
    Chromosome& operator=(const Chromosome&);
};