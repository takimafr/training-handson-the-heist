import { Module } from '@nestjs/common';
import { EmployeeModule } from './employee/employee.module';
import { AuthenticationModule } from './authentication/authentication.module';

@Module({
  imports: [EmployeeModule, AuthenticationModule],
  controllers: [],
  providers: [],
})
export class AppModule {}
