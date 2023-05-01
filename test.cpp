  switch (prefixed_opcode)
        {
        case 0x00:
            {
                spdlog::info("RLC B {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x01:
            {
                spdlog::info("RLC C {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x02:
            {
                spdlog::info("RLC D {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x03:
            {
                spdlog::info("RLC E {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x04:
            {
                spdlog::info("RLC H {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x05:
            {
                spdlog::info("RLC L {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x06:
            {
                spdlog::info("RLC (HL) {:X}", prefixed_opcode);
                this->RLC_2B_4C(&cycles);
                break;
            }
        case 0x07:
            {
                spdlog::info("RLC A {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        
        case 0x08:
            {
                spdlog::info("RRC B {:X}", prefixed_opcode);
                this->RRC_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x09:
            {
                spdlog::info("RRC C {:X}", prefixed_opcode);
                this->RRC_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x0A:
            {
                spdlog::info("RRC D {:X}", prefixed_opcode);
                this->RLC_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x0B:
            {
                spdlog::info("RRC E {:X}", prefixed_opcode);
                this->RRC_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x0C:
            {
                spdlog::info("RRC H {:X}", prefixed_opcode);
                this->RRC_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x0D:
            {
                spdlog::info("RRC L {:X}", prefixed_opcode);
                this->RRC_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x0E:
            {
                spdlog::info("RRC (HL) {:X}", prefixed_opcode);
                this->RRC_2B_4C(&cycles);
                break;
            }
        case 0x0F:
            {
                spdlog::info("RRC A {:X}", prefixed_opcode);
                this->RRC_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        case 0x10:
            {
                spdlog::info("RL B {:X}", prefixed_opcode);
                this->RL_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x11:
            {
                spdlog::info("RL C {:X}", prefixed_opcode);
                this->RL_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x12:
            {
                spdlog::info("RL D {:X}", prefixed_opcode);
                this->RL_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x13:
            {
                spdlog::info("RL E {:X}", prefixed_opcode);
                this->RL_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x14:
            {
                spdlog::info("RL H {:X}", prefixed_opcode);
                this->RL_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x15:
            {
                spdlog::info("RL L {:X}", prefixed_opcode);
                this->RL_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x16:
            {
                spdlog::info("RL (HL) {:X}", prefixed_opcode);
                this->RL_2B_4C(&cycles);
                break;
            }
        case 0x17:
            {
                spdlog::info("RL A {:X}", prefixed_opcode);
                this->RL_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        
        case 0x18:
            {
                spdlog::info("RR B {:X}", prefixed_opcode);
                this->RR_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x19:
            {
                spdlog::info("RR C {:X}", prefixed_opcode);
                this->RR_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x1A:
            {
                spdlog::info("RR D {:X}", prefixed_opcode);
                this->RR_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x1B:
            {
                spdlog::info("RR E {:X}", prefixed_opcode);
                this->RR_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x1C:
            {
                spdlog::info("RR H {:X}", prefixed_opcode);
                this->RR_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x1D:
            {
                spdlog::info("RR L {:X}", prefixed_opcode);
                this->RR_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x1E:
            {
                spdlog::info("RR (HL) {:X}", prefixed_opcode);
                this->RR_2B_4C(&cycles);
                break;
            }
        case 0x1F:
            {
                spdlog::info("RR A {:X}", prefixed_opcode);
                this->RR_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        case 0x20:
            {
                spdlog::info("SLA B {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x21:
            {
                spdlog::info("SLA C {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x22:
            {
                spdlog::info("SLA D {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x23:
            {
                spdlog::info("SLA E {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x24:
            {
                spdlog::info("SLA H {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x25:
            {
                spdlog::info("SLA L {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x26:
            {
                spdlog::info("SLA (HL) {:X}", prefixed_opcode);
                this->SLA_2B_4C(&cycles);
                break;
            }
        case 0x27:
            {
                spdlog::info("SLA A {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        
        case 0x28:
            {
                spdlog::info("SRA B {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x29:
            {
                spdlog::info("SRA C {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x2A:
            {
                spdlog::info("SRA D {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x2B:
            {
                spdlog::info("SRA E {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x2C:
            {
                spdlog::info("SRA H {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x2D:
            {
                spdlog::info("SRA L {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x2E:
            {
                spdlog::info("SRA (HL) {:X}", prefixed_opcode);
                this->SRA_2B_4C(&cycles);
                break;
            }
        case 0x2F:
            {
                spdlog::info("SRA A {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        case 0x30:
            {
                spdlog::info("SWAP B {:X}", prefixed_opcode);
                this->SWAP_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x31:
            {
                spdlog::info("SWAP C {:X}", prefixed_opcode);
                this->SLA_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x32:
            {
                spdlog::info("SWAP D {:X}", prefixed_opcode);
                this->SWAP_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x33:
            {
                spdlog::info("SWAP E {:X}", prefixed_opcode);
                this->SWAP_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x34:
            {
                spdlog::info("SWAP H {:X}", prefixed_opcode);
                this->SWAP_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x35:
            {
                spdlog::info("SWAP L {:X}", prefixed_opcode);
                this->SWAP_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x36:
            {
                spdlog::info("SWAP (HL) {:X}", prefixed_opcode);
                this->SWAP_2B_4C(&cycles);
                break;
            }
        case 0x37:
            {
                spdlog::info("SWAP A {:X}", prefixed_opcode);
                this->SWAP_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        
        case 0x38:
            {
                spdlog::info("SRA B {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.BC.B,&cycles);
                break;
            }
        case 0x39:
            {
                spdlog::info("SRA C {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.BC.C,&cycles);
                break;
            }
        case 0x3A:
            {
                spdlog::info("SRA D {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.DE.D,&cycles);
                break;
            }
        case 0x3B:
            {
                spdlog::info("SRA E {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.DE.E,&cycles);
                break;
            }
        case 0x3C:
            {
                spdlog::info("SRA H {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.HL.H,&cycles);
                break;
            }
        case 0x3D:
            {
                spdlog::info("SRA L {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.HL.L,&cycles);
                break;
            }
        case 0x3E:
            {
                spdlog::info("SRA (HL) {:X}", prefixed_opcode);
                this->SRA_2B_4C(&cycles);
                break;
            }
        case 0x3F:
            {
                spdlog::info("SRA A {:X}", prefixed_opcode);
                this->SRA_2B_2C(&this->registers->registers.AF.A,&cycles);
                break;
            }
        case 0x40:
            {
                spdlog::info("BIT 1, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x41:
            {
                spdlog::info("BIT 1, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x42:
            {
                spdlog::info("BIT 1, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x43:
            {
                spdlog::info("BIT 1, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x44:
            {
                spdlog::info("BIT 1, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x45:
            {
                spdlog::info("BIT 1, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x46:
            {
                spdlog::info("BIT 1, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(1, &cycles);
                break;
            }
        case 0x47:
            {
                spdlog::info("BIT 1, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x48:
            {
                spdlog::info("BIT 1, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x49:
            {
                spdlog::info("BIT 1, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x4A:
            {
                spdlog::info("BIT 1, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x4B:
            {
                spdlog::info("BIT 1, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x4C:
            {
                spdlog::info("BIT 1, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x4D:
            {
                spdlog::info("BIT 1, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x4E:
            {
                spdlog::info("BIT 1, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(1, &cycles);
                break;
            }
        case 0x4F:
            {
                spdlog::info("BIT 1, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(1,this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x50:
            {
                spdlog::info("BIT 2, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(2,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x51:
            {
                spdlog::info("BIT 2, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(2,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x52:
            {
                spdlog::info("BIT 2, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(2,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x53:
            {
                spdlog::info("BIT 2, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(2,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x54:
            {
                spdlog::info("BIT 2, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(2,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x55:
            {
                spdlog::info("BIT 2, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(2,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x56:
            {
                spdlog::info("BIT 2, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(2, &cycles);
                break;
            }
        case 0x57:
            {
                spdlog::info("BIT 2, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(2,this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x58:
            {
                spdlog::info("BIT 3, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(3,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x59:
            {
                spdlog::info("BIT 3, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(3,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x5A:
            {
                spdlog::info("BIT 3, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(3,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x5B:
            {
                spdlog::info("BIT 3, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(3,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x5C:
            {
                spdlog::info("BIT 3, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(3,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x5D:
            {
                spdlog::info("BIT 3, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(3,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x5E:
            {
                spdlog::info("BIT 3, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(3, &cycles);
                break;
            }
        case 0x5F:
            {
                spdlog::info("BIT 3, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(3,this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x60:
            {
                spdlog::info("BIT 4, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(4,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x61:
            {
                spdlog::info("BIT 4, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(4,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x62:
            {
                spdlog::info("BIT 4, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(4,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x63:
            {
                spdlog::info("BIT 4, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(4,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x64:
            {
                spdlog::info("BIT 4, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(4,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x65:
            {
                spdlog::info("BIT 4, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(4,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x66:
            {
                spdlog::info("BIT 4, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(4, &cycles);
                break;
            }
        case 0x67:
            {
                spdlog::info("BIT 4, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(4,this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x68:
            {
                spdlog::info("BIT 5, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(5,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x69:
            {
                spdlog::info("BIT 5, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(5,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x6A:
            {
                spdlog::info("BIT 5, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(5,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x6B:
            {
                spdlog::info("BIT 5, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(5,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x6C:
            {
                spdlog::info("BIT 5, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(5,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x6D:
            {
                spdlog::info("BIT 5, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(5,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x6E:
            {
                spdlog::info("BIT 5, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(5, &cycles);
                break;
            }
        case 0x6F:
            {
                spdlog::info("BIT 5, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(5,this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x70:
            {
                spdlog::info("BIT 6, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(6,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x71:
            {
                spdlog::info("BIT 6, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(6,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x72:
            {
                spdlog::info("BIT 6, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(6,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x73:
            {
                spdlog::info("BIT 6, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(6,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x74:
            {
                spdlog::info("BIT 6, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(6,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x75:
            {
                spdlog::info("BIT 6, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(6,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x76:
            {
                spdlog::info("BIT 6, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(6, &cycles);
                break;
            }
        case 0x77:
            {
                spdlog::info("BIT 6, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(6,this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x78:
            {
                spdlog::info("BIT 7, B {:X}", prefixed_opcode);
                this->BIT_2B_2C(7,this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x79:
            {
                spdlog::info("BIT 7, C {:X}", prefixed_opcode);
                this->BIT_2B_2C(7,this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x7A:
            {
                spdlog::info("BIT 7, D {:X}", prefixed_opcode);
                this->BIT_2B_2C(7,this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x7B:
            {
                spdlog::info("BIT 7, E {:X}", prefixed_opcode);
                this->BIT_2B_2C(7,this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x7C:
            {
                spdlog::info("BIT 7, H {:X}", prefixed_opcode);
                this->BIT_2B_2C(7,this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x7D:
            {
                spdlog::info("BIT 7, L {:X}", prefixed_opcode);
                this->BIT_2B_2C(7,this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x7E:
            {
                spdlog::info("BIT 7, L {:X}", prefixed_opcode);
                this->BIT_2B_3C(7, &cycles);
                break;
            }
        case 0x7F:
            {
                spdlog::info("BIT 7, A {:X}", prefixed_opcode);
                this->BIT_2B_2C(7,this->registers->registers.AF.A, &cycles);
                break;
            }
                case 0x80:
            {
                spdlog::info("RES 1, B {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x81:
            {
                spdlog::info("RES 1, C {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x82:
            {
                spdlog::info("RES 1, D {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x83:
            {
                spdlog::info("RES 1, E {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x84:
            {
                spdlog::info("RES 1, H {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x85:
            {
                spdlog::info("RES 1, L {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x86:
            {
                spdlog::info("RES 1, L {:X}", prefixed_opcode);
                this->RES_2B_4C(1, &cycles);
                break;
            }
        case 0x87:
            {
                spdlog::info("RES 1, A {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x88:
            {
                spdlog::info("RES 1, B {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x89:
            {
                spdlog::info("RES 1, C {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x8A:
            {
                spdlog::info("RES 1, D {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x8B:
            {
                spdlog::info("RES 1, E {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x8C:
            {
                spdlog::info("RES 1, H {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x8D:
            {
                spdlog::info("RES 1, L {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x8E:
            {
                spdlog::info("RES 1, L {:X}", prefixed_opcode);
                this->RES_2B_4C(1, &cycles);
                break;
            }
        case 0x8F:
            {
                spdlog::info("RES 1, A {:X}", prefixed_opcode);
                this->RES_2B_2C(1,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x90:
            {
                spdlog::info("RES 2, B {:X}", prefixed_opcode);
                this->RES_2B_2C(2,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x91:
            {
                spdlog::info("RES 2, C {:X}", prefixed_opcode);
                this->RES_2B_2C(2,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x92:
            {
                spdlog::info("RES 2, D {:X}", prefixed_opcode);
                this->RES_2B_2C(2,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x93:
            {
                spdlog::info("RES 2, E {:X}", prefixed_opcode);
                this->RES_2B_2C(2,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x94:
            {
                spdlog::info("RES 2, H {:X}", prefixed_opcode);
                this->RES_2B_2C(2,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x95:
            {
                spdlog::info("RES 2, L {:X}", prefixed_opcode);
                this->RES_2B_2C(2,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x96:
            {
                spdlog::info("RES 2, L {:X}", prefixed_opcode);
                this->RES_2B_4C(2, &cycles);
                break;
            }
        case 0x97:
            {
                spdlog::info("RES 2, A {:X}", prefixed_opcode);
                this->RES_2B_2C(2,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0x98:
            {
                spdlog::info("RES 3, B {:X}", prefixed_opcode);
                this->RES_2B_2C(3,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0x99:
            {
                spdlog::info("RES 3, C {:X}", prefixed_opcode);
                this->RES_2B_2C(3,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0x9A:
            {
                spdlog::info("RES 3, D {:X}", prefixed_opcode);
                this->RES_2B_2C(3,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0x9B:
            {
                spdlog::info("RES 3, E {:X}", prefixed_opcode);
                this->RES_2B_2C(3,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0x9C:
            {
                spdlog::info("RES 3, H {:X}", prefixed_opcode);
                this->RES_2B_2C(3,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0x9D:
            {
                spdlog::info("RES 3, L {:X}", prefixed_opcode);
                this->RES_2B_2C(3,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0x9E:
            {
                spdlog::info("RES 3, L {:X}", prefixed_opcode);
                this->RES_2B_4C(3, &cycles);
                break;
            }
        case 0x9F:
            {
                spdlog::info("RES 3, A {:X}", prefixed_opcode);
                this->RES_2B_2C(3,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xA0:
            {
                spdlog::info("RES 4, B {:X}", prefixed_opcode);
                this->RES_2B_2C(4,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xA1:
            {
                spdlog::info("RES 4, C {:X}", prefixed_opcode);
                this->RES_2B_2C(4,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xA2:
            {
                spdlog::info("RES 4, D {:X}", prefixed_opcode);
                this->RES_2B_2C(4,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xA3:
            {
                spdlog::info("RES 4, E {:X}", prefixed_opcode);
                this->RES_2B_2C(4,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xA4:
            {
                spdlog::info("RES 4, H {:X}", prefixed_opcode);
                this->RES_2B_2C(4,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xA5:
            {
                spdlog::info("RES 4, L {:X}", prefixed_opcode);
                this->RES_2B_2C(4,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xA6:
            {
                spdlog::info("RES 4, L {:X}", prefixed_opcode);
                this->RES_2B_4C(4, &cycles);
                break;
            }
        case 0xA7:
            {
                spdlog::info("RES 4, A {:X}", prefixed_opcode);
                this->RES_2B_2C(4,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xA8:
            {
                spdlog::info("RES 5, B {:X}", prefixed_opcode);
                this->RES_2B_2C(5,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xA9:
            {
                spdlog::info("RES 5, C {:X}", prefixed_opcode);
                this->RES_2B_2C(5,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xAA:
            {
                spdlog::info("RES 5, D {:X}", prefixed_opcode);
                this->RES_2B_2C(5,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xAB:
            {
                spdlog::info("RES 5, E {:X}", prefixed_opcode);
                this->RES_2B_2C(5,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xAC:
            {
                spdlog::info("RES 5, H {:X}", prefixed_opcode);
                this->RES_2B_2C(5,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xAD:
            {
                spdlog::info("RES 5, L {:X}", prefixed_opcode);
                this->RES_2B_2C(5,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xAE:
            {
                spdlog::info("RES 5, L {:X}", prefixed_opcode);
                this->RES_2B_4C(5, &cycles);
                break;
            }
        case 0xAF:
            {
                spdlog::info("RES 5, A {:X}", prefixed_opcode);
                this->RES_2B_2C(5,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xB0:
            {
                spdlog::info("RES 6, B {:X}", prefixed_opcode);
                this->RES_2B_2C(6,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xB1:
            {
                spdlog::info("RES 6, C {:X}", prefixed_opcode);
                this->RES_2B_2C(6,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xB2:
            {
                spdlog::info("RES 6, D {:X}", prefixed_opcode);
                this->RES_2B_2C(6,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xB3:
            {
                spdlog::info("RES 6, E {:X}", prefixed_opcode);
                this->RES_2B_2C(6,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xB4:
            {
                spdlog::info("RES 6, H {:X}", prefixed_opcode);
                this->RES_2B_2C(6,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xB5:
            {
                spdlog::info("RES 6, L {:X}", prefixed_opcode);
                this->RES_2B_2C(6,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xB6:
            {
                spdlog::info("RES 6, L {:X}", prefixed_opcode);
                this->RES_2B_4C(6, &cycles);
                break;
            }
        case 0xB7:
            {
                spdlog::info("RES 6, A {:X}", prefixed_opcode);
                this->RES_2B_2C(6,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xB8:
            {
                spdlog::info("RES 7, B {:X}", prefixed_opcode);
                this->RES_2B_2C(7,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xB9:
            {
                spdlog::info("RES 7, C {:X}", prefixed_opcode);
                this->RES_2B_2C(7,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xBA:
            {
                spdlog::info("RES 7, D {:X}", prefixed_opcode);
                this->RES_2B_2C(7,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xBB:
            {
                spdlog::info("RES 7, E {:X}", prefixed_opcode);
                this->RES_2B_2C(7,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xBC:
            {
                spdlog::info("RES 7, H {:X}", prefixed_opcode);
                this->RES_2B_2C(7,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xBD:
            {
                spdlog::info("RES 7, L {:X}", prefixed_opcode);
                this->RES_2B_2C(7,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xBE:
            {
                spdlog::info("RES 7, L {:X}", prefixed_opcode);
                this->RES_2B_4C(7, &cycles);
                break;
            }
        case 0xBF:
            {
                spdlog::info("RES 7, A {:X}", prefixed_opcode);
                this->RES_2B_2C(7,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xC0:
            {
                spdlog::info("SET 1, B {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xC1:
            {
                spdlog::info("SET 1, C {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xC2:
            {
                spdlog::info("SET 1, D {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xC3:
            {
                spdlog::info("SET 1, E {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xC4:
            {
                spdlog::info("SET 1, H {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xC5:
            {
                spdlog::info("SET 1, L {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xC6:
            {
                spdlog::info("SET 1, L {:X}", prefixed_opcode);
                this->SET_2B_4C(1, &cycles);
                break;
            }
        case 0xC7:
            {
                spdlog::info("SET 1, A {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xC8:
            {
                spdlog::info("SET 1, B {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xC9:
            {
                spdlog::info("SET 1, C {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xCA:
            {
                spdlog::info("SET 1, D {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xCB:
            {
                spdlog::info("SET 1, E {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xCC:
            {
                spdlog::info("SET 1, H {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xCD:
            {
                spdlog::info("SET 1, L {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xCE:
            {
                spdlog::info("SET 1, L {:X}", prefixed_opcode);
                this->SET_2B_4C(1, &cycles);
                break;
            }
        case 0xCF:
            {
                spdlog::info("SET 1, A {:X}", prefixed_opcode);
                this->SET_2B_2C(1,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xD0:
            {
                spdlog::info("SET 2, B {:X}", prefixed_opcode);
                this->SET_2B_2C(2,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xD1:
            {
                spdlog::info("SET 2, C {:X}", prefixed_opcode);
                this->SET_2B_2C(2,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xD2:
            {
                spdlog::info("SET 2, D {:X}", prefixed_opcode);
                this->SET_2B_2C(2,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xD3:
            {
                spdlog::info("SET 2, E {:X}", prefixed_opcode);
                this->SET_2B_2C(2,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xD4:
            {
                spdlog::info("SET 2, H {:X}", prefixed_opcode);
                this->SET_2B_2C(2,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xD5:
            {
                spdlog::info("SET 2, L {:X}", prefixed_opcode);
                this->SET_2B_2C(2,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xD6:
            {
                spdlog::info("SET 2, L {:X}", prefixed_opcode);
                this->SET_2B_4C(2, &cycles);
                break;
            }
        case 0xD7:
            {
                spdlog::info("SET 2, A {:X}", prefixed_opcode);
                this->SET_2B_2C(2,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xD8:
            {
                spdlog::info("SET 3, B {:X}", prefixed_opcode);
                this->SET_2B_2C(3,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xD9:
            {
                spdlog::info("SET 3, C {:X}", prefixed_opcode);
                this->SET_2B_2C(3,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xDA:
            {
                spdlog::info("SET 3, D {:X}", prefixed_opcode);
                this->SET_2B_2C(3,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xDB:
            {
                spdlog::info("SET 3, E {:X}", prefixed_opcode);
                this->SET_2B_2C(3,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xDC:
            {
                spdlog::info("SET 3, H {:X}", prefixed_opcode);
                this->SET_2B_2C(3,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xDD:
            {
                spdlog::info("SET 3, L {:X}", prefixed_opcode);
                this->SET_2B_2C(3,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xDE:
            {
                spdlog::info("SET 3, L {:X}", prefixed_opcode);
                this->SET_2B_4C(3, &cycles);
                break;
            }
        case 0xDF:
            {
                spdlog::info("SET 3, A {:X}", prefixed_opcode);
                this->SET_2B_2C(3,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xE0:
            {
                spdlog::info("SET 4, B {:X}", prefixed_opcode);
                this->SET_2B_2C(4,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xE1:
            {
                spdlog::info("SET 4, C {:X}", prefixed_opcode);
                this->SET_2B_2C(4,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xE2:
            {
                spdlog::info("SET 4, D {:X}", prefixed_opcode);
                this->SET_2B_2C(4,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xE3:
            {
                spdlog::info("SET 4, E {:X}", prefixed_opcode);
                this->SET_2B_2C(4,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xE4:
            {
                spdlog::info("SET 4, H {:X}", prefixed_opcode);
                this->SET_2B_2C(4,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xE5:
            {
                spdlog::info("SET 4, L {:X}", prefixed_opcode);
                this->SET_2B_2C(4,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xE6:
            {
                spdlog::info("SET 4, L {:X}", prefixed_opcode);
                this->SET_2B_4C(4, &cycles);
                break;
            }
        case 0xE7:
            {
                spdlog::info("SET 4, A {:X}", prefixed_opcode);
                this->SET_2B_2C(4,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xE8:
            {
                spdlog::info("SET 5, B {:X}", prefixed_opcode);
                this->SET_2B_2C(5,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xE9:
            {
                spdlog::info("SET 5, C {:X}", prefixed_opcode);
                this->SET_2B_2C(5,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xEA:
            {
                spdlog::info("SET 5, D {:X}", prefixed_opcode);
                this->SET_2B_2C(5,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xEB:
            {
                spdlog::info("SET 5, E {:X}", prefixed_opcode);
                this->SET_2B_2C(5,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xEC:
            {
                spdlog::info("SET 5, H {:X}", prefixed_opcode);
                this->SET_2B_2C(5,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xED:
            {
                spdlog::info("SET 5, L {:X}", prefixed_opcode);
                this->SET_2B_2C(5,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xEE:
            {
                spdlog::info("SET 5, L {:X}", prefixed_opcode);
                this->SET_2B_4C(5, &cycles);
                break;
            }
        case 0xEF:
            {
                spdlog::info("SET 5, A {:X}", prefixed_opcode);
                this->SET_2B_2C(5,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xF0:
            {
                spdlog::info("SET 6, B {:X}", prefixed_opcode);
                this->SET_2B_2C(6,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xF1:
            {
                spdlog::info("SET 6, C {:X}", prefixed_opcode);
                this->SET_2B_2C(6,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xF2:
            {
                spdlog::info("SET 6, D {:X}", prefixed_opcode);
                this->SET_2B_2C(6,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xF3:
            {
                spdlog::info("SET 6, E {:X}", prefixed_opcode);
                this->SET_2B_2C(6,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xF4:
            {
                spdlog::info("SET 6, H {:X}", prefixed_opcode);
                this->SET_2B_2C(6,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xF5:
            {
                spdlog::info("SET 6, L {:X}", prefixed_opcode);
                this->SET_2B_2C(6,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xF6:
            {
                spdlog::info("SET 6, L {:X}", prefixed_opcode);
                this->SET_2B_4C(6, &cycles);
                break;
            }
        case 0xF7:
            {
                spdlog::info("SET 6, A {:X}", prefixed_opcode);
                this->SET_2B_2C(6,&this->registers->registers.AF.A, &cycles);
                break;
            }
        case 0xF8:
            {
                spdlog::info("SET 7, B {:X}", prefixed_opcode);
                this->SET_2B_2C(7,&this->registers->registers.BC.B, &cycles);
                break;
            }
        
        case 0xF9:
            {
                spdlog::info("SET 7, C {:X}", prefixed_opcode);
                this->SET_2B_2C(7,&this->registers->registers.BC.C, &cycles);
                break;
            }
        case 0xFA:
            {
                spdlog::info("SET 7, D {:X}", prefixed_opcode);
                this->SET_2B_2C(7,&this->registers->registers.DE.D, &cycles);
                break;
            }
        case 0xFB:
            {
                spdlog::info("SET 7, E {:X}", prefixed_opcode);
                this->SET_2B_2C(7,&this->registers->registers.DE.E, &cycles);
                break;
            }
        
        case 0xFC:
            {
                spdlog::info("SET 7, H {:X}", prefixed_opcode);
                this->SET_2B_2C(7,&this->registers->registers.HL.H, &cycles);
                break;
            }
        case 0xFD:
            {
                spdlog::info("SET 7, L {:X}", prefixed_opcode);
                this->SET_2B_2C(7,&this->registers->registers.HL.L, &cycles);
                break;
            }
        case 0xFE:
            {
                spdlog::info("SET 7, L {:X}", prefixed_opcode);
                this->SET_2B_4C(7, &cycles);
                break;
            }
        case 0xFF:
            {
                spdlog::info("SET 7, A {:X}", prefixed_opcode);
                this->SET_2B_2C(7,&this->registers->registers.AF.A, &cycles);
                break;
            }
        
        
        
            
        
        default:
        {
            spdlog::info("Unimplemented 16 bit {:X}", prefixed_opcode);
            break;
        }
        
        }
        break;