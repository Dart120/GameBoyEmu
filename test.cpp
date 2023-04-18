        case 0xC0:
            {
                spdlog::info("SET 1, B {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xC1:
            {
                spdlog::info("SET 1, C {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xC2:
            {
                spdlog::info("SET 1, D {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xC3:
            {
                spdlog::info("SET 1, E {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xC4:
            {
                spdlog::info("SET 1, H {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xC5:
            {
                spdlog::info("SET 1, L {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xC6:
            {
                spdlog::info("SET 1, L {:X}", opcode);
                this->SET_2B_4C(1, &cycles);
                break;
            }
        case 0xC7:
            {
                spdlog::info("SET 1, A {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xC8:
            {
                spdlog::info("SET 1, B {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xC9:
            {
                spdlog::info("SET 1, C {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xCA:
            {
                spdlog::info("SET 1, D {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xCB:
            {
                spdlog::info("SET 1, E {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xCC:
            {
                spdlog::info("SET 1, H {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xCD:
            {
                spdlog::info("SET 1, L {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xCE:
            {
                spdlog::info("SET 1, L {:X}", opcode);
                this->SET_2B_4C(1, &cycles);
                break;
            }
        case 0xCF:
            {
                spdlog::info("SET 1, A {:X}", opcode);
                this->SET_2B_2C(1,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xD0:
            {
                spdlog::info("SET 2, B {:X}", opcode);
                this->SET_2B_2C(2,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xD1:
            {
                spdlog::info("SET 2, C {:X}", opcode);
                this->SET_2B_2C(2,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xD2:
            {
                spdlog::info("SET 2, D {:X}", opcode);
                this->SET_2B_2C(2,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xD3:
            {
                spdlog::info("SET 2, E {:X}", opcode);
                this->SET_2B_2C(2,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xD4:
            {
                spdlog::info("SET 2, H {:X}", opcode);
                this->SET_2B_2C(2,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xD5:
            {
                spdlog::info("SET 2, L {:X}", opcode);
                this->SET_2B_2C(2,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xD6:
            {
                spdlog::info("SET 2, L {:X}", opcode);
                this->SET_2B_4C(2, &cycles);
                break;
            }
        case 0xD7:
            {
                spdlog::info("SET 2, A {:X}", opcode);
                this->SET_2B_2C(2,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xD8:
            {
                spdlog::info("SET 3, B {:X}", opcode);
                this->SET_2B_2C(3,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xD9:
            {
                spdlog::info("SET 3, C {:X}", opcode);
                this->SET_2B_2C(3,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xDA:
            {
                spdlog::info("SET 3, D {:X}", opcode);
                this->SET_2B_2C(3,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xDB:
            {
                spdlog::info("SET 3, E {:X}", opcode);
                this->SET_2B_2C(3,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xDC:
            {
                spdlog::info("SET 3, H {:X}", opcode);
                this->SET_2B_2C(3,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xDD:
            {
                spdlog::info("SET 3, L {:X}", opcode);
                this->SET_2B_2C(3,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xDE:
            {
                spdlog::info("SET 3, L {:X}", opcode);
                this->SET_2B_4C(3, &cycles);
                break;
            }
        case 0xDF:
            {
                spdlog::info("SET 3, A {:X}", opcode);
                this->SET_2B_2C(3,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xE0:
            {
                spdlog::info("SET 4, B {:X}", opcode);
                this->SET_2B_2C(4,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xE1:
            {
                spdlog::info("SET 4, C {:X}", opcode);
                this->SET_2B_2C(4,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xE2:
            {
                spdlog::info("SET 4, D {:X}", opcode);
                this->SET_2B_2C(4,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xE3:
            {
                spdlog::info("SET 4, E {:X}", opcode);
                this->SET_2B_2C(4,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xE4:
            {
                spdlog::info("SET 4, H {:X}", opcode);
                this->SET_2B_2C(4,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xE5:
            {
                spdlog::info("SET 4, L {:X}", opcode);
                this->SET_2B_2C(4,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xE6:
            {
                spdlog::info("SET 4, L {:X}", opcode);
                this->SET_2B_4C(4, &cycles);
                break;
            }
        case 0xE7:
            {
                spdlog::info("SET 4, A {:X}", opcode);
                this->SET_2B_2C(4,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xE8:
            {
                spdlog::info("SET 5, B {:X}", opcode);
                this->SET_2B_2C(5,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xE9:
            {
                spdlog::info("SET 5, C {:X}", opcode);
                this->SET_2B_2C(5,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xEA:
            {
                spdlog::info("SET 5, D {:X}", opcode);
                this->SET_2B_2C(5,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xEB:
            {
                spdlog::info("SET 5, E {:X}", opcode);
                this->SET_2B_2C(5,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xEC:
            {
                spdlog::info("SET 5, H {:X}", opcode);
                this->SET_2B_2C(5,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xED:
            {
                spdlog::info("SET 5, L {:X}", opcode);
                this->SET_2B_2C(5,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xEE:
            {
                spdlog::info("SET 5, L {:X}", opcode);
                this->SET_2B_4C(5, &cycles);
                break;
            }
        case 0xEF:
            {
                spdlog::info("SET 5, A {:X}", opcode);
                this->SET_2B_2C(5,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xF0:
            {
                spdlog::info("SET 6, B {:X}", opcode);
                this->SET_2B_2C(6,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xF1:
            {
                spdlog::info("SET 6, C {:X}", opcode);
                this->SET_2B_2C(6,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xF2:
            {
                spdlog::info("SET 6, D {:X}", opcode);
                this->SET_2B_2C(6,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xF3:
            {
                spdlog::info("SET 6, E {:X}", opcode);
                this->SET_2B_2C(6,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xF4:
            {
                spdlog::info("SET 6, H {:X}", opcode);
                this->SET_2B_2C(6,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xF5:
            {
                spdlog::info("SET 6, L {:X}", opcode);
                this->SET_2B_2C(6,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xF6:
            {
                spdlog::info("SET 6, L {:X}", opcode);
                this->SET_2B_4C(6, &cycles);
                break;
            }
        case 0xF7:
            {
                spdlog::info("SET 6, A {:X}", opcode);
                this->SET_2B_2C(6,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xF8:
            {
                spdlog::info("SET 7, B {:X}", opcode);
                this->SET_2B_2C(7,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xF9:
            {
                spdlog::info("SET 7, C {:X}", opcode);
                this->SET_2B_2C(7,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xFA:
            {
                spdlog::info("SET 7, D {:X}", opcode);
                this->SET_2B_2C(7,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xFB:
            {
                spdlog::info("SET 7, E {:X}", opcode);
                this->SET_2B_2C(7,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xFC:
            {
                spdlog::info("SET 7, H {:X}", opcode);
                this->SET_2B_2C(7,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xFD:
            {
                spdlog::info("SET 7, L {:X}", opcode);
                this->SET_2B_2C(7,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xFE:
            {
                spdlog::info("SET 7, L {:X}", opcode);
                this->SET_2B_4C(7, &cycles);
                break;
            }
        case 0xFF:
            {
                spdlog::info("SET 7, A {:X}", opcode);
                this->SET_2B_2C(7,&this->registers->registers.AF.A, &cycles);
                break;
            }