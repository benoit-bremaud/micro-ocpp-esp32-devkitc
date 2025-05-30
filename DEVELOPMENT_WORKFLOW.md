# Workflow de développement

## 1. Création d'une issue

Avant toute implémentation, créer une issue GitHub avec :

- **Titre** : `[CATEGORY] Nom de la fonctionnalité`
- **Labels** : `enhancement`, `ocpp-core` ou `ocpp-optional`
- **Description** : Référence OCPP, objectifs, critères d'acceptation

## 2. Structure d'une fonctionnalité

\`\`\`bash
features/category/feature_name/
├── README.md                    # Documentation + lien issue
├── feature_handler.h           # Interface
├── feature_handler.cpp         # Implémentation  
├── schemas/                    # Schémas JSON OCPP
│   ├── request.json
│   └── response.json
└── tests/                      # Tests unitaires
    └── test_feature.cpp
\`\`\`

## 3. Checklist de développement

- [ ] Issue GitHub créée et assignée
- [ ] Branche feature créée : `feature/issue-number-feature-name`
- [ ] Implémentation avec tests
- [ ] Documentation mise à jour
- [ ] Pull Request avec référence à l'issue
- [ ] Review et merge

## 4. Standards de code

- **Headers** : Guards d'inclusion, documentation Doxygen
- **Tests** : Couverture minimale 80%
- **Validation** : Conformité schémas OCPP 1.6
- **Logging** : Messages d'erreur explicites
