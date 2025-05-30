# Tests Unitaires et d'Intégration

## Structure

- `unit/` - Tests unitaires des composants individuels
- `integration/` - Tests d'intégration système

## Exécution

```bash
# Tous les tests
pio test

# Tests unitaires seulement
pio test --filter unit

# Tests d'intégration seulement
pio test --filter integration
