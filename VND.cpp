#include "Solution.hpp"
#include "SwapIntra.cpp"
#include "SwapInter.cpp"
#include "Reinsertion.cpp"

void buscaLocal(Solution& s, SwapIntra& swintra, SwapInter& swinter, Reinsertion& reinsertion)
{
    int k = 1;
    
    Solution best_solution = Solution(s);
    double melhor_custo = best_solution.custo_total;
    
    while (k <= 3)
    {
        switch (k)
        {
            case 1:
                swintra.run(s);
                break;
        
            case 2:
                swinter.run(s);
                break;

            case 3:
                reinsertion.run(s);
                break;
            
        }
        
        s.calcula_custo_total();

        if (s.custo_total < melhor_custo)
        {
            best_solution = Solution(s);
            melhor_custo = s.custo_total;
            k = 1;
        }
        else
        {
            k++;
        }
    }

    s = Solution(best_solution);

}
