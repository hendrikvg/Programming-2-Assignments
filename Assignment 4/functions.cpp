void printCosts(std::vector<Package*> packages)
{
    for (size_t i = 0; i < packages.size(); i++)
    {
        printf("Cost of shipping package %i is: %.2f \n",i + 1, packages[i]->calculateCost());
    }
}