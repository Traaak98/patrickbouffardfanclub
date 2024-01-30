


    // !!! This file is generated using emlearn !!!

    // #include <eml_trees.h>
    

// EmlTreesNode decision_tree_nodes[79] = {
//   { 334, -0.9998194873332977, 1, 7 },
//   { 816, -0.9999445080757141, 2, 6 },
//   { 922, -0.9926605224609375, 3, 6 },
//   { 8, -0.8822785019874573, 4, 5 },
//   { -1, 1, -1, -1 },
//   { 689, -0.9999400079250336, 6, 4 },
//   { -1, 5, -1, -1 },
//   { 778, -0.7768394947052002, 8, 75 },
//   { 722, -0.9997105002403259, 9, 21 },
//   { 547, -0.8954340219497681, 10, 17 },
//   { 0, -0.9943445026874542, 11, 13 },
//   { 548, -0.9655625224113464, 4, 12 },
//   { -1, 3, -1, -1 },
//   { 995, -0.995772510766983, 14, 6 },
//   { 439, -0.9797060191631317, 15, 16 },
//   { -1, 0, -1, -1 },
//   { -1, 9, -1, -1 },
//   { 63, -0.9837930202484131, 18, 19 },
//   { -1, 2, -1, -1 },
//   { 992, -0.9159605205059052, 20, 15 },
//   { 302, -0.9999125003814697, 16, 6 },
//   { 1021, -0.6116900146007538, 22, 61 },
//   { 809, -0.9984389841556549, 23, 41 },
//   { 1019, -0.7850735187530518, 24, 36 },
//   { 70, -0.849989503622055, 25, 33 },
//   { 514, -0.8843965232372284, 26, 29 },
//   { 865, -0.9907899796962738, 27, 28 },
//   { 33, -0.8908165097236633, 18, 4 },
//   { 528, -0.8628830015659332, 16, 15 },
//   { 148, -0.9893410205841064, 30, 32 },
//   { 506, -0.8400295078754425, 31, 15 },
//   { -1, 8, -1, -1 },
//   { 193, -0.9855625033378601, 12, 18 },
//   { 592, -0.801428496837616, 34, 35 },
//   { -1, 6, -1, -1 },
//   { 833, -0.9745999872684479, 15, 16 },
//   { 104, -0.8936904966831207, 37, 40 },
//   { 608, -0.20160935074090958, 38, 6 },
//   { 490, -0.7498224973678589, 39, 16 },
//   { 132, -0.9994024932384491, 18, 15 },
//   { 119, -0.9781115055084229, 16, 34 },
//   { 104, -0.8165990114212036, 42, 58 },
//   { 514, -0.9166965186595917, 43, 49 },
//   { 528, -0.9753849804401398, 44, 46 },
//   { 370, -0.9860420227050781, 45, 34 },
//   { 852, -0.988583505153656, 31, 16 },
//   { 359, -0.9843465089797974, 47, 48 },
//   { 559, -0.972201019525528, 18, 18 },
//   { 1022, -0.9327584803104401, 16, 18 },
//   { 21, -0.9406979978084564, 50, 54 },
//   { 10, -0.9300580024719238, 51, 53 },
//   { 396, -0.9913845062255859, 31, 52 },
//   { -1, 4, -1, -1 },
//   { 1002, -0.9569484889507294, 16, 52 },
//   { 524, -0.7990875244140625, 55, 56 },
//   { 512, -0.7013469934463501, 12, 52 },
//   { 760, -0.9819390177726746, 6, 57 },
//   { -1, 7, -1, -1 },
//   { 425, -0.821881502866745, 59, 60 },
//   { 990, -0.8590455055236816, 52, 18 },
//   { 596, -0.8700565099716187, 12, 34 },
//   { 438, -0.8418504893779755, 62, 69 },
//   { 940, -0.9355189800262451, 63, 64 },
//   { 764, -0.989206999540329, 16, 57 },
//   { 483, -0.8167470097541809, 65, 68 },
//   { 231, -0.9542964994907379, 66, 67 },
//   { 973, -0.39332249760627747, 52, 12 },
//   { 286, -0.9432969987392426, 57, 31 },
//   { 717, -0.8221955001354218, 12, 57 },
//   { 501, -0.8387015163898468, 70, 71 },
//   { 371, -0.8740924894809723, 57, 12 },
//   { 506, -0.6976760029792786, 72, 73 },
//   { 939, -0.8223665058612823, 16, 52 },
//   { 308, -0.9296430051326752, 34, 74 },
//   { 683, -0.9159179925918579, 57, 31 },
//   { 1014, -0.6921039819717407, 76, 52 },
//   { 535, -0.9694600105285645, 77, 78 },
//   { 997, -0.8217184841632843, 12, 57 },
//   { 66, -0.6052910089492798, 57, 16 } 
// };

int32_t decision_tree_tree_roots[1] = { 0 };

// EmlTrees decision_tree = {
//         79,
//         decision_tree_nodes,	  
//         1,
//         decision_tree_tree_roots,
//     };

static inline int32_t decision_tree_tree_0(const float *features, int32_t features_length) {
          if (features[334] < -0.999819f) {
              if (features[816] < -0.999945f) {
                  if (features[922] < -0.992661f) {
                      if (features[8] < -0.882279f) {
                          return 1;
                      } else {
                          if (features[689] < -0.999940f) {
                              return 5;
                          } else {
                              return 1;
                          }
                      }
                  } else {
                      return 5;
                  }
              } else {
                  return 5;
              }
          } else {
              if (features[778] < -0.776839f) {
                  if (features[722] < -0.999711f) {
                      if (features[547] < -0.895434f) {
                          if (features[0] < -0.994345f) {
                              if (features[548] < -0.965563f) {
                                  return 1;
                              } else {
                                  return 3;
                              }
                          } else {
                              if (features[995] < -0.995773f) {
                                  if (features[439] < -0.979706f) {
                                      return 0;
                                  } else {
                                      return 9;
                                  }
                              } else {
                                  return 5;
                              }
                          }
                      } else {
                          if (features[63] < -0.983793f) {
                              return 2;
                          } else {
                              if (features[992] < -0.915961f) {
                                  if (features[302] < -0.999913f) {
                                      return 9;
                                  } else {
                                      return 5;
                                  }
                              } else {
                                  return 0;
                              }
                          }
                      }
                  } else {
                      if (features[1021] < -0.611690f) {
                          if (features[809] < -0.998439f) {
                              if (features[1019] < -0.785074f) {
                                  if (features[70] < -0.849990f) {
                                      if (features[514] < -0.884397f) {
                                          if (features[865] < -0.990790f) {
                                              if (features[33] < -0.890817f) {
                                                  return 2;
                                              } else {
                                                  return 1;
                                              }
                                          } else {
                                              if (features[528] < -0.862883f) {
                                                  return 9;
                                              } else {
                                                  return 0;
                                              }
                                          }
                                      } else {
                                          if (features[148] < -0.989341f) {
                                              if (features[506] < -0.840030f) {
                                                  return 8;
                                              } else {
                                                  return 0;
                                              }
                                          } else {
                                              if (features[193] < -0.985563f) {
                                                  return 3;
                                              } else {
                                                  return 2;
                                              }
                                          }
                                      }
                                  } else {
                                      if (features[592] < -0.801428f) {
                                          return 6;
                                      } else {
                                          if (features[833] < -0.974600f) {
                                              return 0;
                                          } else {
                                              return 9;
                                          }
                                      }
                                  }
                              } else {
                                  if (features[104] < -0.893690f) {
                                      if (features[608] < -0.201609f) {
                                          if (features[490] < -0.749822f) {
                                              if (features[132] < -0.999402f) {
                                                  return 2;
                                              } else {
                                                  return 0;
                                              }
                                          } else {
                                              return 9;
                                          }
                                      } else {
                                          return 5;
                                      }
                                  } else {
                                      if (features[119] < -0.978112f) {
                                          return 9;
                                      } else {
                                          return 6;
                                      }
                                  }
                              }
                          } else {
                              if (features[104] < -0.816599f) {
                                  if (features[514] < -0.916697f) {
                                      if (features[528] < -0.975385f) {
                                          if (features[370] < -0.986042f) {
                                              if (features[852] < -0.988584f) {
                                                  return 8;
                                              } else {
                                                  return 9;
                                              }
                                          } else {
                                              return 6;
                                          }
                                      } else {
                                          if (features[359] < -0.984347f) {
                                              if (features[559] < -0.972201f) {
                                                  return 2;
                                              } else {
                                                  return 2;
                                              }
                                          } else {
                                              if (features[1022] < -0.932758f) {
                                                  return 9;
                                              } else {
                                                  return 2;
                                              }
                                          }
                                      }
                                  } else {
                                      if (features[21] < -0.940698f) {
                                          if (features[10] < -0.930058f) {
                                              if (features[396] < -0.991385f) {
                                                  return 8;
                                              } else {
                                                  return 4;
                                              }
                                          } else {
                                              if (features[1002] < -0.956948f) {
                                                  return 9;
                                              } else {
                                                  return 4;
                                              }
                                          }
                                      } else {
                                          if (features[524] < -0.799088f) {
                                              if (features[512] < -0.701347f) {
                                                  return 3;
                                              } else {
                                                  return 4;
                                              }
                                          } else {
                                              if (features[760] < -0.981939f) {
                                                  return 5;
                                              } else {
                                                  return 7;
                                              }
                                          }
                                      }
                                  }
                              } else {
                                  if (features[425] < -0.821882f) {
                                      if (features[990] < -0.859046f) {
                                          return 4;
                                      } else {
                                          return 2;
                                      }
                                  } else {
                                      if (features[596] < -0.870057f) {
                                          return 3;
                                      } else {
                                          return 6;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[438] < -0.841850f) {
                              if (features[940] < -0.935519f) {
                                  if (features[764] < -0.989207f) {
                                      return 9;
                                  } else {
                                      return 7;
                                  }
                              } else {
                                  if (features[483] < -0.816747f) {
                                      if (features[231] < -0.954296f) {
                                          if (features[973] < -0.393322f) {
                                              return 4;
                                          } else {
                                              return 3;
                                          }
                                      } else {
                                          if (features[286] < -0.943297f) {
                                              return 7;
                                          } else {
                                              return 8;
                                          }
                                      }
                                  } else {
                                      if (features[717] < -0.822196f) {
                                          return 3;
                                      } else {
                                          return 7;
                                      }
                                  }
                              }
                          } else {
                              if (features[501] < -0.838702f) {
                                  if (features[371] < -0.874092f) {
                                      return 7;
                                  } else {
                                      return 3;
                                  }
                              } else {
                                  if (features[506] < -0.697676f) {
                                      if (features[939] < -0.822367f) {
                                          return 9;
                                      } else {
                                          return 4;
                                      }
                                  } else {
                                      if (features[308] < -0.929643f) {
                                          return 6;
                                      } else {
                                          if (features[683] < -0.915918f) {
                                              return 7;
                                          } else {
                                              return 8;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[1014] < -0.692104f) {
                      if (features[535] < -0.969460f) {
                          if (features[997] < -0.821718f) {
                              return 3;
                          } else {
                              return 7;
                          }
                      } else {
                          if (features[66] < -0.605291f) {
                              return 7;
                          } else {
                              return 9;
                          }
                      }
                  } else {
                      return 4;
                  }
              }
          }
        }
        

int32_t decision_tree_predict(const float *features, int32_t features_length) {

        int32_t votes[10] = {0,};
        int32_t _class = -1;

        _class = decision_tree_tree_0(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<10; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    