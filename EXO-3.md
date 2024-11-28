# Exercice 3

| Scene rendue | Multithreading activé | AABB activé | Temps d'exécution |
|--------------|-----------------------|------------|-------------------|
| iso_sphere_on_plane | Non                   | Non        | 19.689s              |
| iso_sphere_on_plane | Non                   | Oui        | 9.997s              |
| iso_sphere_on_plane | Oui                   | Non        | 4.563s             |
| iso_sphere_on_plane | Oui                   | Oui        | 2.396s             |
| two-spheres-on-plane | Non | Non | 1.469s |
| two-spheres-on-plane | Non | Oui | 1.562s |
| two-spheres-on-plane | Oui | Non | 0.391s |
| two-spheres-on-plane | Oui | Oui | 0.400s |
| monkey-on-plane | Non | Non | 277.989s |
| monkey-on-plane | Non | Oui | 103.237s |
| monkey-on-plane | Oui | Non | 66.559s |
| monkey-on-plane | Oui | Oui | 27.118s |
| all | Non | Non | 509.687s |
| all | Non | Oui | 231.730s |
| all | Oui | Non | 134.283s |
| all| Oui | Oui | 60.679s |
----------------------------------

## Avec AABB sur les meshs

| Scene rendue | Multithreading activé | AABB activé | Temps d'exécution |
|--------------|-----------------------|------------|-------------------|
| all | Oui | Non | 134.283s |
| all | Non | Oui | 122.545s |
| all | Oui | Oui | 32.090s |
| monkey-on-plane | Oui | Non | 66.559s |
| monkey-on-plane | Non | Oui | 27.524s |
| monkey-on-plane | Oui | Oui | 7.769s |

