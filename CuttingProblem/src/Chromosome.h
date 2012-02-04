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
	void						InsertGene(const size_t index, const size_t value);
	void						DeleteGene(const size_t index);
	void						DeleteRectangle( const size_t index );

	RectangleF*					GetRectangle(const size_t index) { return m_RectanglePlacement[index]; }
	const RectangleDB&			GetRectangleDB() { return m_RectanglePlacement; }
	
	inline float&				FitnessValue() {return m_fFitnessValue; }
	inline float&				ProbabilityValue() {return m_fProbabilityValue; }

	bool		                IsPlacement() const { return m_bIsPlacement; }
    void				        SetPlacement(bool bPlacement) { m_bIsPlacement = bPlacement; }

	void						ReInitDB();
	void						WipeDB();

	static Chromosome*			GenerateRandChromosome();
private:
    std::vector<int>			m_iRectangleQueue;

	// Automatically sync with database init rectangles
    RectangleDB					m_RectanglePlacement;
    
	bool						m_bIsPlacement;

	// calculate outside
	float						m_fFitnessValue; // calculate by IFitness
	float						m_fProbabilityValue; // calculate by SelectorRoulette
};