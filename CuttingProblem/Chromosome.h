#pragma once

#include "RectangleDB.h"

#include "wx/thread.h"
#include <vector>

class Chromosome
{
public:
	Chromosome(size_t uiGeneCount = 0);
	~Chromosome();

	Chromosome(const Chromosome&);
	Chromosome& operator=(const Chromosome&);

	const size_t				Size() const { return m_iRectangleQueue.size(); }

	const int					GetGene(const size_t index) const { return m_iRectangleQueue[index]; }
	void						SetGene(const size_t index, const size_t value) { m_iRectangleQueue[index] = value; }
	RectangleF*					GetRectangle(const size_t index) { return m_RectanglePlacement[index]; }
	const RectangleDB&			GetRectangleDB() { return m_RectanglePlacement; }

    bool		                IsPlacement() const { return m_bIsPlacement; }
    void				        SetPlacement(bool bPlacement) { m_bIsPlacement = bPlacement; }

	static Chromosome*			GenerateRandChromosome();

private:
    std::vector<int>			m_iRectangleQueue;

	// Automatically sync with database init rectangles
    RectangleDB					m_RectanglePlacement;
    
	float						m_fFitnessValue;
	bool						m_bIsPlacement;
};