import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AddlogComponent } from './addlog/addlog.component';
import { HomeComponent } from './home/home.component';

const routes: Routes = [
  { path: '', component: HomeComponent },
  { path: 'addlog', component: AddlogComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }