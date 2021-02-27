import Vue from 'vue'

import axios from 'axios'

import { ValidationObserver, ValidationProvider, extend, localize } from 'vee-validate';
import en from 'vee-validate/dist/locale/en.json';
import * as rules from 'vee-validate/dist/rules';

Vue.prototype.$http = axios;
window.Vue = Vue;

Vue.config.productionTip = false;
Vue.config.devtools = true;

Object.keys(rules).forEach(rule => {
    extend(rule, rules[rule]);
});
localize('en', en);

//Example register component:
//Vue.component('loginpartialview', require('./components/login.component.vue').default);
Vue.component('ValidationObserver', ValidationObserver);
Vue.component('ValidationProvider', ValidationProvider);

Vue.component('vuefooter', require('./components/footer.component.vue').default);
Vue.component('loginform', require('./components/login.component.vue').default);
Vue.component('registerform', require('./components/register.component.vue').default);
Vue.component('productdetail', require('./components/pdp.component.vue').default);
Vue.component('product-component', require('./components/product.component.vue').default);
Vue.component('product-list-component', require('./components/product-list.component.vue').default);
Vue.component('cart', require('./components/cart.component.vue').default);
Vue.component('carousel', require('./components/carousel.component.vue').default);
Vue.component('minicart', require('./components/minicart.component.vue').default);