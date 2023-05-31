uint32 mappedValue;

/* MAPPING FUNCTION - FUNÇÃO DE MAPEAMENTO */
int32_t MAP(int32_t au32_IN, int32_t au32_INmin, int32_t au32_INmax, int32_t au32_OUTmin, int32_t au32_OUTmax)
{
    return ((((au32_IN - au32_INmin)*(au32_OUTmax - au32_OUTmin))/(au32_INmax - au32_INmin)) + au32_OUTmin);
}

mappedValue = MAP(Var, 0, 4095, 0, 100);
